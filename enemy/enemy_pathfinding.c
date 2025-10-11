#include "../cube.h"

void try_alternative_directions(t_enemy *enemy, t_parsed_data *pd,
        t_bpos direction, double speed)
{
    t_bpos  alternatives[8];
    t_bpos  new_pos;
    int     map_x;
    int     map_y;
    int     i;

    set_alternative_directions(alternatives, direction);
    i = 0;
    while (i < 8)
    {
        new_pos.x = enemy->b_pos.x + alternatives[i].x * speed;
        new_pos.y = enemy->b_pos.y + alternatives[i].y * speed;
        map_x = (int)new_pos.x;
        map_y = (int)new_pos.y;
        if (is_valid_move_position(pd, map_x, map_y))
        {
            enemy->b_pos = new_pos;
            enemy->dir.x = alternatives[i].x;
            enemy->dir.y = alternatives[i].y;
            return ;
        }
        i++;
    }
}

void smart_chase_player(t_enemy *enemy, t_bpos player_pos, double speed,
        t_parsed_data *pd)
{
    t_bpos  direction;
    t_bpos  new_pos;
    int     map_x;
    int     map_y;

    calculate_direction_to_player(enemy, player_pos, &direction);
    new_pos.x = enemy->b_pos.x + direction.x * speed;
    new_pos.y = enemy->b_pos.y + direction.y * speed;
    map_x = (int)new_pos.x;
    map_y = (int)new_pos.y;
    if (is_valid_move_position(pd, map_x, map_y))
    {
        enemy->b_pos = new_pos;
        enemy->dir.x = direction.x;
        enemy->dir.y = direction.y;
        return ;
    }
    try_alternative_directions(enemy, pd, direction, speed);
}

double calculate_distance_to_player(t_enemy *enemy, t_parsed_data *pd)
{
    double dx;
    double dy;
    double distance;

    dx = enemy->b_pos.x - pd->player.bpos.x;
    dy = enemy->b_pos.y - pd->player.bpos.y;
    distance = sqrt(dx * dx + dy * dy);
    return (distance);
}

 void perform_patrol_movement(t_enemy *enemy, t_parsed_data *pd)
{
    t_bpos  new_pos;
    int     map_x;
    int     map_y;

    new_pos.x = enemy->b_pos.x + enemy->dir.x * enemy->patrol_speed;
    new_pos.y = enemy->b_pos.y + enemy->dir.y * enemy->patrol_speed;
    map_x = (int)new_pos.x;
    map_y = (int)new_pos.y;
    if (map_y >= 0 && map_y < pd->level.max_y
        && map_x >= 0 && map_x < pd->level.max_x
        && pd->map_grid[map_y][map_x] == '0')
    {
        enemy->b_pos = new_pos;
    }
    else
        change_enemy_direction(enemy);
}


void handle_patrol_state(t_enemy_ctx *ctx)
{
	if (ctx->distance <= CHASE_DISTANCE && ctx->visible)
	{
		ctx->enemy->state = ENEMY_CHASE;
		printf("Enemy %d started chasing!\n", ctx->index);
	}
	else
		perform_patrol_movement(ctx->enemy, ctx->pd);
}
