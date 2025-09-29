
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
