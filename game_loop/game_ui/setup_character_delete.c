#include "../../cube.h"

static void delete_shoot_frames(t_parsed_data *pd)
{
    int i;

    if (pd->player.gun.shoot.frames)
    {
        i = 0;
        while (i < pd->player.gun.shoot.frame_count)
        {
            if (pd->player.gun.shoot.frames[i].txtr)
            {
                mlx_delete_texture(pd->player.gun.shoot.frames[i].txtr);
                pd->player.gun.shoot.frames[i].txtr = NULL;
            }
            i++;
        }
    }
}

static void delete_reload_frames(t_parsed_data *pd)
{
    int i;

    if (pd->player.gun.reload.frames)
    {
        i = 0;
        while (i < pd->player.gun.reload.frame_count)
        {
            if (pd->player.gun.reload.frames[i].txtr)
            {
                mlx_delete_texture(pd->player.gun.reload.frames[i].txtr);
                pd->player.gun.reload.frames[i].txtr = NULL;
            }
            i++;
        }
    }
}

void delete_gun_textures(t_parsed_data *pd)
{
    if (pd->game_ui.gun.txtr)
    {
        mlx_delete_texture(pd->game_ui.gun.txtr);
        pd->game_ui.gun.txtr = NULL;
    }
    if (pd->game_ui.gun_aim.txtr)
    {
        mlx_delete_texture(pd->game_ui.gun_aim.txtr);
        pd->game_ui.gun_aim.txtr = NULL;
    }
    delete_shoot_frames(pd);
    delete_reload_frames(pd);
}
