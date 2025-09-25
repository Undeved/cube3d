#include "../cube.h"

static  bool is_wall(char **map_grid, double x, double y, t_parsed_data *pd)
{
    int x_index;
    int y_index;

    x_index = (int)x;
    y_index = (int)y;
    if (x_index <= 0 || y_index <= 0 
        || x_index >= pd->level.max_x 
        || y_index >= pd->level.max_y)
        return (true);
    if (map_grid[y_index][x_index] == '1')
        return (true);
    return (false);
}

static double   direction_check(double dir)
{
    if (dir > 0)
        return (COLLISION);
    else if (dir < 0)
        return (-COLLISION);
    return (0);
}

static void forward_backward(t_parsed_data *pd)
{
    if (pd->keys.pressed[MLX_KEY_W])
    {
        pd->player.new_pos.x += pd->player.bdir.x * SPEED;
        pd->player.new_pos.y += pd->player.bdir.y * SPEED;
        if (!is_wall(pd->map_grid, pd->player.new_pos.x + pd->player.offset.x, pd->player.bpos.y, pd))
            pd->player.bpos.x = pd->player.new_pos.x;
        if (!is_wall(pd->map_grid, pd->player.bpos.x, pd->player.new_pos.y + pd->player.offset.y, pd))
            pd->player.bpos.y = pd->player.new_pos.y;
    }
    if (pd->keys.pressed[MLX_KEY_S])
    {
        pd->player.new_pos.x -= pd->player.bdir.x * SPEED;
        pd->player.new_pos.y -= pd->player.bdir.y * SPEED;
        if (!is_wall(pd->map_grid, pd->player.new_pos.x - pd->player.offset.x, pd->player.bpos.y, pd))
            pd->player.bpos.x = pd->player.new_pos.x;
        if (!is_wall(pd->map_grid, pd->player.bpos.x, pd->player.new_pos.y - pd->player.offset.y, pd))
            pd->player.bpos.y = pd->player.new_pos.y;
    }
}
// collision problems revise entire code
// 7it vector dial side direction perpenducular 
// 3la direction vector, cancalculiw mnha.
static void strafe(t_parsed_data *pd)
{
    if (pd->keys.pressed[MLX_KEY_D])
    {
        pd->player.new_pos.x += pd->player.bdir.y * STRAFE_SPEED;
        pd->player.new_pos.y += -pd->player.bdir.x * STRAFE_SPEED;
        if (!is_wall(pd->map_grid, pd->player.new_pos.x + pd->player.offset.y, pd->player.bpos.y, pd))
            pd->player.bpos.x = pd->player.new_pos.x;
        if (!is_wall(pd->map_grid, pd->player.bpos.x, pd->player.new_pos.y - pd->player.offset.x, pd))
            pd->player.bpos.y = pd->player.new_pos.y;
    }
    if (pd->keys.pressed[MLX_KEY_A])
    {
        pd->player.new_pos.x += -pd->player.bdir.y * STRAFE_SPEED;
        pd->player.new_pos.y += pd->player.bdir.x * STRAFE_SPEED;
        if (!is_wall(pd->map_grid, pd->player.new_pos.x - pd->player.offset.y, pd->player.bpos.y, pd))
            pd->player.bpos.x = pd->player.new_pos.x;
        if (!is_wall(pd->map_grid, pd->player.bpos.x, pd->player.new_pos.y + pd->player.offset.x, pd))
            pd->player.bpos.y = pd->player.new_pos.y;
    }
}

// collision problems revise entire code
// instead of offset use radious implementation.
static void player_movement(t_parsed_data *pd)
{
    pd->player.new_pos.x = pd->player.bpos.x;
    pd->player.new_pos.y = pd->player.bpos.y;
    pd->player.offset.x = direction_check(pd->player.bdir.x);
    pd->player.offset.y = direction_check(pd->player.bdir.y);
    forward_backward(pd);
    strafe(pd);
}

static void player_rotation(t_parsed_data *pd)
{
    if (pd->keys.pressed[MLX_KEY_LEFT])
    {
        double old_x = pd->player.bdir.x;
        double old_y = pd->player.bdir.y;
        // matrix rotation calculation [x', y'] = [x, y] * [x * cos(R) + y * sin(R), x * -sin(R) + y * cos(R)] 
        pd->player.bdir.x = old_x * cos(ROT_SPEED) - old_y * sin(ROT_SPEED);
        pd->player.bdir.y = old_x * sin(ROT_SPEED) + old_y * cos(ROT_SPEED);
    }
    if (pd->keys.pressed[MLX_KEY_RIGHT])
    {
        double old_x = pd->player.bdir.x;
        double old_y = pd->player.bdir.y;
        pd->player.bdir.x = old_x * cos(-ROT_SPEED) - old_y * sin(-ROT_SPEED);
        pd->player.bdir.y = old_x * sin(-ROT_SPEED) + old_y * cos(-ROT_SPEED);

    }
    // Debuggin
    // if (pd->keys.pressed[MLX_KEY_RIGHT] || pd->keys.pressed[MLX_KEY_LEFT])
        // printf("rotation vector ==> v[x=%.2f, y=%.2f]\n", pd->player.bdir.x, pd->player.bdir.y);
}

void    update_player_data(t_parsed_data *pd)
{
    player_movement(pd);
    player_rotation(pd);
}

void    handle_player_input(mlx_key_data_t keydata, void *param)
{
    t_parsed_data *pd;

    pd = param;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS && pd->ui_index != 1)
    {
        mlx_close_window(pd->mlx);
        return ;
        // mind_free_all(EXIT_SUCCESS);
    }
    handle_ui_input(keydata, pd);
    if (!pd->level.game_started)
        return ;
    if (keydata.key >= 0 && keydata.key < KEYS_NUMBER)
    {
        if (keydata.action == MLX_PRESS)
            pd->keys.pressed[keydata.key] = true;
        else if (keydata.action == MLX_RELEASE)
            pd->keys.pressed[keydata.key] = false;
    }
}
