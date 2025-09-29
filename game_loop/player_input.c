#include "../cube.h"

static bool is_collision(char **map_grid, double x, double y)
{
    if (map_grid[(int)y][(int)x] == '1')
        return (true);
    if (map_grid[(int)y][(int)(x + COLLISION)] == '1'
        || map_grid[(int)y][(int)(x - COLLISION)] == '1')
        return (true);
    if (map_grid[(int)(y + COLLISION)][(int)x] == '1' 
        || map_grid[(int)(y - COLLISION)][(int)x] == '1')
        return (true); 
    return (false);
}


static void forward_backward(t_parsed_data *pd)
{
    if (pd->keys.pressed[MLX_KEY_W])
    {
        pd->player.new_pos.x += pd->player.bdir.x * SPEED;
        pd->player.new_pos.y += pd->player.bdir.y * SPEED;
        if (!is_collision(pd->map_grid, pd->player.new_pos.x, pd->player.bpos.y))
            pd->player.bpos.x = pd->player.new_pos.x;
        if (!is_collision(pd->map_grid, pd->player.bpos.x, pd->player.new_pos.y))
            pd->player.bpos.y = pd->player.new_pos.y;
    }
    if (pd->keys.pressed[MLX_KEY_S])
    {
        pd->player.new_pos.x -= pd->player.bdir.x * SPEED;
        pd->player.new_pos.y -= pd->player.bdir.y * SPEED;
        if (!is_collision(pd->map_grid, pd->player.new_pos.x, pd->player.bpos.y))
            pd->player.bpos.x = pd->player.new_pos.x;
        if (!is_collision(pd->map_grid, pd->player.bpos.x, pd->player.new_pos.y))
            pd->player.bpos.y = pd->player.new_pos.y;
    }
}

static void strafe(t_parsed_data *pd)
{
    if (pd->keys.pressed[MLX_KEY_A])
    {
        pd->player.new_pos.x += pd->player.bdir.y * STRAFE_SPEED;
        pd->player.new_pos.y += -pd->player.bdir.x * STRAFE_SPEED;
        if (!is_collision(pd->map_grid, pd->player.new_pos.x, pd->player.bpos.y))
            pd->player.bpos.x = pd->player.new_pos.x;
        if (!is_collision(pd->map_grid, pd->player.bpos.x, pd->player.new_pos.y))
            pd->player.bpos.y = pd->player.new_pos.y;
    }
    if (pd->keys.pressed[MLX_KEY_D])
    {
        pd->player.new_pos.x += -pd->player.bdir.y * STRAFE_SPEED;
        pd->player.new_pos.y += pd->player.bdir.x * STRAFE_SPEED;
        if (!is_collision(pd->map_grid, pd->player.new_pos.x, pd->player.bpos.y))
            pd->player.bpos.x = pd->player.new_pos.x;
        if (!is_collision(pd->map_grid, pd->player.bpos.x, pd->player.new_pos.y))
            pd->player.bpos.y = pd->player.new_pos.y;
    }
}

static void player_movement(t_parsed_data *pd)
{
    pd->player.new_pos.x = pd->player.bpos.x;
    pd->player.new_pos.y = pd->player.bpos.y;
    forward_backward(pd);
    strafe(pd);
}

static void player_rotation(t_parsed_data *pd)
{
    if (pd->keys.pressed[MLX_KEY_RIGHT])
    {
        double old_x = pd->player.bdir.x;
        double old_y = pd->player.bdir.y;
        // matrix rotation calculation [x', y'] = [x, y] * [x * cos(R) + y * sin(R), x * -sin(R) + y * cos(R)] 
        pd->player.bdir.x = old_x * cos(ROT_SPEED) - old_y * sin(ROT_SPEED);
        pd->player.bdir.y = old_x * sin(ROT_SPEED) + old_y * cos(ROT_SPEED);
    }
    if (pd->keys.pressed[MLX_KEY_LEFT])
    {
        double old_x = pd->player.bdir.x;
        double old_y = pd->player.bdir.y;
        pd->player.bdir.x = old_x * cos(-ROT_SPEED) - old_y * sin(-ROT_SPEED);
        pd->player.bdir.y = old_x * sin(-ROT_SPEED) + old_y * cos(-ROT_SPEED);

    }
    
    // mouse rotation
    int delta_x = pd->mouse.x - (WIDTH / 2);
    if (delta_x != 0)
    {
        double angle = delta_x * MOUSE_SENSITIVITY;
        double old_x = pd->player.bdir.x;
        double old_y = pd->player.bdir.y;

        pd->player.bdir.x = old_x * cos(angle) - old_y * sin(angle);
        pd->player.bdir.y = old_x * sin(angle) + old_y * cos(angle);
    }
    mlx_set_mouse_pos(pd->mlx, WIDTH / 2, HEIGHT / 2);
    
    // Debuggin
    // if (pd->keys.pressed[MLX_KEY_RIGHT] || pd->keys.pressed[MLX_KEY_LEFT])
        // printf("rotation vector ==> v[x=%.2f, y=%.2f]\n", pd->player.bdir.x, pd->player.bdir.y);
}
// might remove just for debegguing
static void update_vignette(mlx_key_data_t keydata, t_parsed_data *pd)
{
    if (keydata.action == MLX_PRESS)
    {
        if (keydata.key == MLX_KEY_SPACE)
        {
            if (pd->game_ui.vignette.img->enabled)
                pd->game_ui.vignette.img->enabled = false;
            else
                pd->game_ui.vignette.img->enabled = true;
        }
    }
}

static void player_pitch(t_parsed_data *pd)
{
    (void)pd;
    if (pd->keys.pressed[MLX_KEY_UP] || pd->mouse.y < (HEIGHT / 2))
    {
        pd->player.pitch += PITCH_SPEED;
        if (pd->player.pitch > MAX_PITCH)
            pd->player.pitch = MAX_PITCH;
    }
    if (pd->keys.pressed[MLX_KEY_DOWN] || pd->mouse.y > (HEIGHT / 2))
    {
        pd->player.pitch -= PITCH_SPEED;
        if (pd->player.pitch < MIN_PITCH)
            pd->player.pitch = MIN_PITCH;
    }
}

void    update_player_data(t_parsed_data *pd)
{
    int32_t m_x;
    int32_t m_y;

    m_x = 0;
    m_y = 0;
    player_movement(pd);
    mlx_get_mouse_pos(pd->mlx, &m_x, &m_y); // get mouse pos to update rot.
    pd->mouse.x = m_x;
    pd->mouse.y = m_y;
    player_rotation(pd);
    player_pitch(pd);
}

void    handle_player_input(mlx_key_data_t keydata, void *param)
{
    t_parsed_data *pd;

    pd = param;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS && pd->ui_index != 1)
    {
        mlx_close_window(pd->mlx);
        return ;
    }
    handle_ui_input(keydata, pd);
    if (!pd->level.game_started)
        return ;
    if (keydata.key >= 0 && keydata.key < KEYS_NUMBER)
    {
        update_vignette(keydata, pd); // update onscreen vignette
        if (keydata.action == MLX_RELEASE)
            pd->keys.pressed[keydata.key] = false;
        else
            pd->keys.pressed[keydata.key] = true;
    }
}
