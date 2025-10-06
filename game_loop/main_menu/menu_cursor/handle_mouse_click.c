#include "../../../cube.h"

#include <sys/time.h>

static long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

static void	trigger_shoot_anim(t_parsed_data *pd)
{
	t_gun *gun = &pd->player.gun;
	t_ui_anim *anim = &gun->shoot;

	if (gun->ammo <= 0)
	{
		printf("Click! No ammo left!\n");
		return;
	}

	gun->ammo--;

	anim->active = true;
	anim->current = 0;
	anim->last_frame_time = current_time_ms();
	anim->frame_delay = 50; // 50 ms between frames (adjust as needed)
}

void trigger_reload_anim(t_parsed_data *pd)
{
    t_gun *gun = &pd->player.gun;
    t_ui_anim *anim = &gun->reload;

    anim->active = true;
    anim->current = 0;
    anim->last_frame_time = current_time_ms();
    anim->frame_delay = 50;
}

// update the animation frame based on time
void	update_ui_anim(t_ui_anim *anim)
{
    if (!anim->active)
        return;

    long now = current_time_ms();
    if (now - anim->last_frame_time >= anim->frame_delay)
    {
        anim->current++;
        if (anim->current >= anim->frame_count)
        {
            anim->current = 0;
            anim->active = false; // stop animation after one loop
        }
        anim->last_frame_time = now;
    }
}


void	render_gun(t_parsed_data *pd)
{
	t_gun *gun;
    int i;

    gun = &pd->player.gun;
    // disable all gun images initially
    pd->game_ui.gun.img->enabled = false;
    pd->game_ui.gun_aim.img->enabled = false;
    i = 0;
    while (i < pd->player.gun.shoot.frame_count)
        pd->player.gun.shoot.frames[i++].img->enabled = false;
    i = 0;
    while (i < pd->player.gun.reload.frame_count)
        pd->player.gun.reload.frames[i++].img->enabled = false;
	if (gun->shoot.active)
		pd->player.gun.shoot.frames[pd->player.gun.shoot.current].img->enabled = true;
    else if (gun->reload.active)
        pd->player.gun.reload.frames[pd->player.gun.reload.current].img->enabled = true;
	else if (gun->aiming)
		pd->game_ui.gun_aim.img->enabled = true;
	else
		pd->game_ui.gun.img->enabled = true;
}


static void game_mouse_input(mouse_key_t button, action_t action, modifier_key_t mods, t_parsed_data *pd)
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
            trigger_shoot_anim(pd);
            printf("Bang! Ammo left: %d\n", pd->player.gun.ammo);
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

void handle_mouse_click(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
    t_parsed_data *pd;

    pd = param;
    (void)mods; // could be used with shift and alt
    game_mouse_input(button, action, mods, pd);
    if (pd->level.game_started || pd->ui_index == 2)
        return ;
    if (action == MLX_PRESS)
    {
        if (button == MLX_MOUSE_BUTTON_LEFT)
        {
            pd->mouse_clicked = true;
            if (pd->ui_index == 0)
                menu_trigger_click(pd);
            else if (pd->ui_index == 1)
                characters_trigger_click(pd);
        }
    }
    else
    {
        if (button == MLX_MOUSE_BUTTON_LEFT)
            pd->mouse_clicked = false;
    }
}
