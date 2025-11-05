#include "../../../cube.h"

void trigger_reload_anim(t_parsed_data *pd)
{
    t_gun *gun = &pd->player.gun;
    t_ui_anim *anim = &gun->reload;

    anim->active = true;
    anim->current = 0;
    anim->last_frame_time = current_time_ms();
    if (pd->player.character == CHORUS || pd->player.character == OUSSMAC)
        anim->frame_delay = 95;
    else
        anim->frame_delay = 50;
}

static bool trigger_shoot_anim(t_parsed_data *pd)
{
	t_gun *gun = &pd->player.gun;
	t_ui_anim *anim = &gun->shoot;

	if (gun->ammo <= 0)
		return (false);
	gun->ammo--;
	anim->active = true;
	anim->current = 0;
	anim->last_frame_time = current_time_ms();
	anim->frame_delay = 50; // 50 ms between frames (adjust as needed)
    return (true);
}

void game_mouse_input(mouse_key_t button, action_t action, modifier_key_t mods, t_parsed_data *pd)
{
    if (pd->ui_index != 2)
        return ;
    (void)mods;
    if (action == MLX_PRESS || action == MLX_REPEAT)
    {
        if (button == MLX_MOUSE_BUTTON_RIGHT)
            pd->player.gun.aiming = true;
        else if (button == MLX_MOUSE_BUTTON_LEFT)
        {
            pd->player.is_shooting = false;
            if (trigger_shoot_anim(pd))
                pd->player.is_shooting = true;
            return ;
        }
    }
    else
    {
        if (button == MLX_MOUSE_BUTTON_RIGHT)
            pd->player.gun.aiming = false;
        else if (button == MLX_MOUSE_BUTTON_LEFT)
            pd->player.is_shooting = false;
    }
    
}

