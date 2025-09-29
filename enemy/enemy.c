
#include "../cube.h"

static bool has_line_of_sight(t_parsed_data *pd, t_bpos start, t_bpos end)
{
    t_bpos delta;
    t_bpos step;
    t_bpos current;
    double max_dist;
    double dist;
    int map_x, map_y;

    delta.x = end.x - start.x;
    delta.y = end.y - start.y;
    
    // Calculate distance between points
    max_dist = sqrt(delta.x * delta.x + delta.y * delta.y);
    
    // Normalize step size for smoother checking
    step.x = delta.x / (max_dist * 4.0);
    step.y = delta.y / (max_dist * 4.0);
    
    current = start;
    dist = 0.0;
    
    while (dist < max_dist)
    {
        current.x += step.x;
        current.y += step.y;
        dist += sqrt(step.x * step.x + step.y * step.y);
        
        if (dist >= max_dist)
            break;
            
        map_x = (int)current.x;
        map_y = (int)current.y;
        
        if (map_y < 0 || map_y >= pd->level.max_y || 
            map_x < 0 || map_x >= pd->level.max_x)
            return false;
        
        if (pd->map_grid[map_y][map_x] == '1')
            return false;
    }
    
    return true;
}

static uint32_t get_enemy_color(t_enemy_type type, double distance, bool visible)
{
    uint32_t base_color;
    
    switch (type)
    {
        case FT_SKIN_WALKER:
            base_color = 0xFF0000FF;
            break;
        case MEMORY_LEAK:
            base_color = 0x00FF00FF;
            break;
        case SEGV:
            base_color = 0x0000FFFF;
            break;
        default:
            base_color = 0xFFFFFFFF;
    }
    
    if (!visible)
        return 0x00000000;
    
    if (distance > 8.0)
    {
        double darken_factor = 1.0 - ((distance - 8.0) / 16.0);
        if (darken_factor < 0.3) darken_factor = 0.3;
        
        uint32_t r = ((base_color >> 24) & 0xFF) * darken_factor;
        uint32_t g = ((base_color >> 16) & 0xFF) * darken_factor;
        uint32_t b = ((base_color >> 8) & 0xFF) * darken_factor;
        
        return (r << 24) | (g << 16) | (b << 8) | 0xFF;
    }
    
    return base_color;
}

// Structure to hold enemy drawing data for sorting
typedef struct s_enemy_draw_data
{
    t_enemy     *enemy;
    double      distance;
    bool        visible;
    t_bpos      transform;
    int         sprite_screen_x;
    int         sprite_height;
    int         sprite_width;
}   t_enemy_draw_data;

// Simple bubble sort for enemies by distance (farthest first)
static void sort_enemies_by_distance(t_enemy_draw_data *draw_data, int count)
{
    int         i;
    int         j;
    t_enemy_draw_data temp;

    i = 0;
    while (i < count - 1)
    {
        j = 0;
        while (j < count - i - 1)
        {
            if (draw_data[j].distance < draw_data[j + 1].distance)
            {
                temp = draw_data[j];
                draw_data[j] = draw_data[j + 1];
                draw_data[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

void    draw_enemies(t_parsed_data *pd)
{
    int                 i;
    int                 draw_count;
    t_enemy_draw_data   draw_data[MAX_ENEMIES];
    t_bpos              rel_pos;
    double              inv_det;
    uint32_t            color;
    int                 stripe;
    int                 draw_start_y, draw_end_y;
    int                 draw_start_x, draw_end_x;

    if (!pd->enemies || pd->enemy_count == 0)
        return ;

    // First pass: collect all visible enemies and compute their drawing data
    draw_count = 0;
    i = 0;
    while (i < pd->enemy_count && draw_count < MAX_ENEMIES)
    {
        if (pd->enemies[i].dead)
        {
            i++;
            continue;
        }

        // Calculate distance and visibility
        rel_pos.x = pd->enemies[i].b_pos.x - pd->player.bpos.x;
        rel_pos.y = pd->enemies[i].b_pos.y - pd->player.bpos.y;
        double distance = sqrt(rel_pos.x * rel_pos.x + rel_pos.y * rel_pos.y);
        bool visible = has_line_of_sight(pd, pd->player.bpos, pd->enemies[i].b_pos);
        
        // Skip if too far or not visible
        if (distance > 24.0 || !visible)
        {
            i++;
            continue;
        }
        
        // Compute transformation
        inv_det = 1.0 / (pd->player.camera_plane.dir.x * pd->player.bdir.y - 
                         pd->player.bdir.x * pd->player.camera_plane.dir.y);
        
        t_bpos transform;
        transform.x = -inv_det * (pd->player.bdir.y * rel_pos.x - pd->player.bdir.x * rel_pos.y);
        transform.y = inv_det * (-pd->player.camera_plane.dir.y * rel_pos.x + pd->player.camera_plane.dir.x * rel_pos.y);
        
        // Skip if behind camera
        if (transform.y <= 0)
        {
            i++;
            continue;
        }
        
        // Store drawing data for sorting
        draw_data[draw_count].enemy = &pd->enemies[i];
        draw_data[draw_count].distance = distance;
        draw_data[draw_count].visible = visible;
        draw_data[draw_count].transform = transform;
        draw_data[draw_count].sprite_screen_x = (int)((WIDTH / 2) * (1 + transform.x / transform.y));
        draw_data[draw_count].sprite_height = abs((int)(HEIGHT / transform.y));
        draw_data[draw_count].sprite_width = abs((int)(HEIGHT / transform.y));
        
        draw_count++;
        i++;
    }
    
    // Sort enemies by distance (farthest first)
    if (draw_count > 1)
        sort_enemies_by_distance(draw_data, draw_count);
    
    // Second pass: draw enemies from farthest to closest
    i = 0;

    while (i < draw_count)
    {
        t_enemy_draw_data *curr = &draw_data[i];

        // zdt had chi 7to fchi function -------------------
        int horizon = HEIGHT / 2 + (int)pd->player.pitch;

        draw_start_y = -curr->sprite_height / 2 + horizon;
        if (draw_start_y < 0) 
            draw_start_y = 0;
        draw_end_y   =  curr->sprite_height / 2 + horizon;
        if (draw_end_y >= HEIGHT) 
            draw_end_y = HEIGHT - 1;
        
        draw_start_x = -curr->sprite_width / 2 + curr->sprite_screen_x;
        if (draw_start_x < 0) draw_start_x = 0;
        draw_end_x = curr->sprite_width / 2 + curr->sprite_screen_x;
        if (draw_end_x >= WIDTH) draw_end_x = WIDTH - 1;
        
        // Get color
        color = get_enemy_color(curr->enemy->type, curr->distance, curr->visible);
        
        // Draw the enemy
        stripe = draw_start_x;
        while (stripe < draw_end_x)
        {
            // relative x inside the sprite
            int tex_x = (int)( (stripe - draw_start_x) * curr->enemy->skin.img->width / curr->sprite_width );

            int y = draw_start_y;
            while (y < draw_end_y)
            {
                // relative y inside the sprite
                int tex_y = (int)( (y - draw_start_y) * curr->enemy->skin.img->height / curr->sprite_height );

                unsigned char *p = (unsigned char *)curr->enemy->skin.img->pixels;
                int idx = (tex_y * curr->enemy->skin.img->width + tex_x) * 4;
                unsigned int r = p[idx + 0];
                unsigned int g = p[idx + 1];
                unsigned int b = p[idx + 2];
                unsigned int a = p[idx + 3];

                uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
                if (a != 0)
                    mlx_put_pixel(pd->screen, stripe, y, shade_color(color, curr->distance, 0.04));

                y++;
            }
            stripe++;
        }

        i++;
    }
}
// Add this function to update enemy positions and patrol behavior
// Function to change enemy direction when hitting walls
static void change_enemy_direction(t_enemy *enemy)
{
    double  directions[4][2] = {
        {0, 1},    // Up
        {1, 0},    // Right  
        {0, -1},   // Down
        {-1, 0}    // Left
    };
    
    int current_dir_index = -1;
    
    // Find current direction index
    for (int i = 0; i < 4; i++)
    {
        if (fabs(enemy->dir.x - directions[i][0]) < 0.1 && 
            fabs(enemy->dir.y - directions[i][1]) < 0.1)
        {
            current_dir_index = i;
            break;
        }
    }
    
    // Try different directions (prioritize perpendicular turns)
    int new_dir_index;
    if (current_dir_index != -1)
    {
        // Try turning 90 degrees left or right
        int turn_direction = (rand() % 2) ? 1 : -1;
        new_dir_index = (current_dir_index + turn_direction + 4) % 4;
        
        // Set new direction
        enemy->dir.x = directions[new_dir_index][0];
        enemy->dir.y = directions[new_dir_index][1];
    }
    else
    {
        // Random direction if current not found
        new_dir_index = rand() % 4;
        enemy->dir.x = directions[new_dir_index][0];
        enemy->dir.y = directions[new_dir_index][1];
    }
}

static void chase_player(t_enemy *enemy, t_bpos player_pos, double speed, t_parsed_data *pd)
{
    t_bpos  direction;
    t_bpos  new_pos;
    int     map_x, map_y;
    
    // Calculate direction towards player
    direction.x = player_pos.x - enemy->b_pos.x;
    direction.y = player_pos.y - enemy->b_pos.y;
    
    // Normalize the direction vector
    double length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0)
    {
        direction.x /= length;
        direction.y /= length;
    }
    
    // Calculate new position
    new_pos.x = enemy->b_pos.x + direction.x * speed;
    new_pos.y = enemy->b_pos.y + direction.y * speed;
    
    // Check if new position is valid
    map_x = (int)new_pos.x;
    map_y = (int)new_pos.y;
    
    if (map_y >= 0 && map_y < pd->level.max_y && 
        map_x >= 0 && map_x < pd->level.max_x &&
        pd->map_grid[map_y][map_x] == '0')
    {
        enemy->b_pos = new_pos;
        enemy->dir.x = direction.x; // Update facing direction
        enemy->dir.y = direction.y;
    }
    // If path is blocked, the enemy will get stuck until player moves
    // You could add pathfinding here for more advanced behavior
}

// Function to return to patrol area
static bool return_to_patrol(t_enemy *enemy, t_parsed_data *pd)
{
    t_bpos  direction;
    t_bpos  new_pos;
    int     map_x, map_y;
    double  distance_to_origin;
    
    // Calculate distance to patrol origin
    distance_to_origin = sqrt(pow(enemy->b_pos.x - enemy->patrol_origin.x, 2) + 
                             pow(enemy->b_pos.y - enemy->patrol_origin.y, 2));
    
    // If close enough to origin, we're done
    if (distance_to_origin < 0.5)
        return true;
    
    // Calculate direction towards patrol origin
    direction.x = enemy->patrol_origin.x - enemy->b_pos.x;
    direction.y = enemy->patrol_origin.y - enemy->b_pos.y;
    
    // Normalize the direction vector
    double length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0)
    {
        direction.x /= length;
        direction.y /= length;
    }
    
    // Calculate new position
    new_pos.x = enemy->b_pos.x + direction.x * enemy->patrol_speed;
    new_pos.y = enemy->b_pos.y + direction.y * enemy->patrol_speed;
    
    // Check if new position is valid
    map_x = (int)new_pos.x;
    map_y = (int)new_pos.y;
    
    if (map_y >= 0 && map_y < pd->level.max_y && 
        map_x >= 0 && map_x < pd->level.max_x &&
        pd->map_grid[map_y][map_x] == '0')
    {
        enemy->b_pos = new_pos;
        enemy->dir.x = direction.x;
        enemy->dir.y = direction.y;
    }
    else
    {
        // If path is blocked, try a different direction
        change_enemy_direction(enemy);
    }
    
    return false;
}


// Fix the heuristic function - use abs for integers
static double heuristic(t_pos a, t_pos b)
{
    return (abs(a.x - b.x) + abs(a.y - b.y)); // Use abs for integers
}

// Simple obstacle-aware chase function
static void smart_chase_player(t_enemy *enemy, t_bpos player_pos, double speed, t_parsed_data *pd)
{
    t_bpos direction;
    t_bpos new_pos;
    int map_x, map_y;
    
    // Calculate direction towards player
    direction.x = player_pos.x - enemy->b_pos.x;
    direction.y = player_pos.y - enemy->b_pos.y;
    
    // Normalize the direction vector
    double length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0)
    {
        direction.x /= length;
        direction.y /= length;
    }
    
    // Try direct movement first
    new_pos.x = enemy->b_pos.x + direction.x * speed;
    new_pos.y = enemy->b_pos.y + direction.y * speed;
    
    map_x = (int)new_pos.x;
    map_y = (int)new_pos.y;
    
    if (map_y >= 0 && map_y < pd->level.max_y && 
        map_x >= 0 && map_x < pd->level.max_x &&
        pd->map_grid[map_y][map_x] == '0')
    {
        // Direct path is clear - move toward player
        enemy->b_pos = new_pos;
        enemy->dir.x = direction.x;
        enemy->dir.y = direction.y;
        return;
    }
    
    // Direct path blocked - try alternative directions (wall sliding)
    t_bpos alternatives[8] = {
        {direction.x, direction.y},           // Original direction (0°)
        {direction.x * 0.7, direction.y * 0.7}, // Slower original
        {direction.y, -direction.x},          // Perpendicular right (90°)
        {-direction.y, direction.x},          // Perpendicular left (-90°)
        {direction.x * 0.7, direction.y * 0.7}, // Slower original again
        {direction.y * 0.7, -direction.x * 0.7}, // Slower right
        {-direction.y * 0.7, direction.x * 0.7}, // Slower left
        {-direction.x, -direction.y}          // Opposite (last resort)
    };
    
    for (int i = 0; i < 8; i++)
    {
        new_pos.x = enemy->b_pos.x + alternatives[i].x * speed;
        new_pos.y = enemy->b_pos.y + alternatives[i].y * speed;
        
        map_x = (int)new_pos.x;
        map_y = (int)new_pos.y;
        
        if (map_y >= 0 && map_y < pd->level.max_y && 
            map_x >= 0 && map_x < pd->level.max_x &&
            pd->map_grid[map_y][map_x] == '0')
        {
            // Found a valid alternative direction
            enemy->b_pos = new_pos;
            enemy->dir.x = alternatives[i].x;
            enemy->dir.y = alternatives[i].y;
            return;
        }
    }
    
    // If all directions blocked and we're stuck for too long, consider returning to patrol
    // For now, just don't move - enemy will be stuck until path clears
}

// Enhanced update_enemies function with smart chasing
void    update_enemies(t_parsed_data *pd)
{
    int         i;
    t_enemy     *enemy;
    double      distance_to_player;
    bool        can_see_player;

    if (!pd->enemies || pd->enemy_count == 0)
        return ;

    i = 0;
    while (i < pd->enemy_count)
    {
        enemy = &pd->enemies[i];
        
        if (enemy->dead)
        {
            i++;
            continue;
        }

        // Calculate distance and visibility to player
        distance_to_player = sqrt(pow(enemy->b_pos.x - pd->player.bpos.x, 2) + 
                                 pow(enemy->b_pos.y - pd->player.bpos.y, 2));
        can_see_player = has_line_of_sight(pd, enemy->b_pos, pd->player.bpos);

        // State machine for enemy behavior
        switch (enemy->state)
        {
            case ENEMY_PATROL:
                // Check if player is close enough and visible to start chase
                if (distance_to_player <= CHASE_DISTANCE && can_see_player)
                {
                    enemy->state = ENEMY_CHASE;
                    printf("Enemy %d started chasing!\n", i);
                }
                else
                {
                    // Continue with normal patrol movement
                    t_bpos new_pos;
                    new_pos.x = enemy->b_pos.x + enemy->dir.x * enemy->patrol_speed;
                    new_pos.y = enemy->b_pos.y + enemy->dir.y * enemy->patrol_speed;
                    
                    // Check if new position is valid
                    int map_x = (int)new_pos.x;
                    int map_y = (int)new_pos.y;
                    
                    if (map_y >= 0 && map_y < pd->level.max_y && 
                        map_x >= 0 && map_x < pd->level.max_x &&
                        pd->map_grid[map_y][map_x] == '0')
                    {
                        enemy->b_pos = new_pos;
                    }
                    else
                    {
                        change_enemy_direction(enemy);
                    }
                }
                break;
                
            case ENEMY_CHASE:
                // Check if player got too far
                if (distance_to_player > LOSE_DISTANCE)
                {
                    enemy->state = ENEMY_RETURN;
                    printf("Enemy %d lost player, returning to patrol!\n", i);
                }
                else if (distance_to_player <= ATTACK_DISTANCE)
                {
                    enemy->state = ENEMY_ATTACK;
                    printf("Enemy %d is attacking!\n", i);
                }
                else
                {
                    // Smart chase - will navigate around obstacles
                    smart_chase_player(enemy, pd->player.bpos, enemy->chase_speed, pd);
                }
                break;
                
            case ENEMY_ATTACK:
                // Check if player moved away from attack range
                if (distance_to_player > ATTACK_DISTANCE)
                {
                    if (distance_to_player <= LOSE_DISTANCE)
                    {
                        enemy->state = ENEMY_CHASE;
                        printf("Enemy %d resumed chasing!\n", i);
                    }
                    else
                    {
                        enemy->state = ENEMY_RETURN;
                        printf("Enemy %d lost player after attack!\n", i);
                    }
                }
                break;
                
            case ENEMY_RETURN:
                // Return to patrol area
                if (return_to_patrol(enemy, pd))
                {
                    enemy->state = ENEMY_PATROL;
                    printf("Enemy %d returned to patrol!\n", i);
                }
                break;
        }

        i++;
    }
}
