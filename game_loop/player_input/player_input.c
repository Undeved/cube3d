#include "../../cube.h"

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

static void reload_gun(t_parsed_data *pd)
{
    if (pd->keys.pressed[MLX_KEY_R] && pd->player.gun.ammo < AMMO && !pd->player.gun.reload.active)
    {
        pd->player.gun.reload.active = true;
        pd->player.gun.shoot.active = false;
        pd->player.gun.aiming = false;
        pd->player.gun.ammo = AMMO;
        printf("Reloading... Ammo refilled to %d\n", pd->player.gun.ammo);
        trigger_reload_anim(pd);
    }
}

// cooldown using gettimeofday letting game to run a bit more then exiting here
// use static variable and let game run multiple times before exiting
static bool cool_down(long usec)
{
    static struct timeval start = {0};
    static bool running = false;

    if (!running)
    {
        gettimeofday(&start, NULL);
        running = true;
        return false;
    }
    struct timeval current;
    gettimeofday(&current, NULL);
    long elapsed = (current.tv_sec - start.tv_sec) * 1000000L + (current.tv_usec - start.tv_usec);
    if (elapsed >= usec)
    {
        running = false;
        return true;
    }
    return false;
}

void    update_player_data(t_parsed_data *pd)
{
    int32_t m_x;
    int32_t m_y;

    m_x = 0;
    m_y = 0;
    if (pd->player.health <= 0)
    {
        pd->game_ui.game_over.img->enabled = true;
        pd->player.is_dead = true;
        if (cool_down(1000000))
        {
            pd->player.health = 0;
            printf("You died! Game Over!\n");
            mind_free_all(EXIT_SUCCESS);
        }
    }
    player_movement(pd);
    mlx_get_mouse_pos(pd->mlx, &m_x, &m_y);
    pd->mouse.x = m_x;
    pd->mouse.y = m_y;
    player_rotation(pd);
    player_pitch(pd);
    interact_with_door(pd);
    update_health_ui(pd);
    reload_gun(pd);
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
        if (keydata.action == MLX_RELEASE)
            pd->keys.pressed[keydata.key] = false;
        else
            pd->keys.pressed[keydata.key] = true;
    }
}
