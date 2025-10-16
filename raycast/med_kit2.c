#include "../cube.h"

void	set_medkit_type_props(t_med_kit *medkit, t_enemy_type type)
{
	if (type == FT_SKIN_WALKER)
		medkit->hp = 20;
	else if (type == MEMORY_LEAK)
		medkit->hp = 30;
	else if (type == SEGV)
		medkit->hp = 40;
	else
		medkit->hp = 25;
	medkit->size_scale = 0.5f;
	medkit->vertical_offset = 1.1f;
}

void	spawn_medkit(t_parsed_data *pd, t_bpos pos, t_enemy_type type)
{
	t_med_kit	*medkit;

	if (pd->medkit_count >= pd->max_medkits)
		return;
	medkit = &pd->medkits[pd->medkit_count];
	medkit->pos = pos;
	medkit->picked = false;
	set_medkit_type_props(medkit, type);
	medkit->img = pd->medkits[0].img;
	pd->medkit_count++;
}

int	process_medkit_pickup(t_parsed_data *pd, int i)
{
	double	dx;
	double	dy;
	double	distance;

	dx = pd->medkits[i].pos.x - pd->player.bpos.x;
	dy = pd->medkits[i].pos.y - pd->player.bpos.y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance < 0.8)
	{
		pd->player.health += pd->medkits[i].hp;
		if (pd->player.health > PLAYER_HEALTH)
			pd->player.health = PLAYER_HEALTH;
		pd->medkits[i].picked = true;
		return (1);
	}
	return (0);
}

void	check_medkit_pickup(t_parsed_data *pd)
{
	int	i;
	int	picked_count;

	i = 0;
	picked_count = 0;
	while (i < pd->medkit_count)
	{
		if (pd->medkits[i].picked)
		{
			if (i < pd->medkit_count - 1)
				pd->medkits[i] = pd->medkits[pd->medkit_count - 1];
			pd->medkit_count--;
			picked_count++;
			continue ;
		}
		picked_count += process_medkit_pickup(pd, i);
		if (pd->medkits[i].picked)
			continue ;
		i++;
	}
}

bool medkit_visible(t_parsed_data *pd, t_med_kit *medkit, t_medkit_draw_data *out)
{
    t_bpos rel_pos;
    double distance;
    double inv_det;
    t_bpos transform;

    rel_pos.x = medkit->pos.x - pd->player.bpos.x;
    rel_pos.y = medkit->pos.y - pd->player.bpos.y;
    distance = sqrt(rel_pos.x * rel_pos.x + rel_pos.y * rel_pos.y);
    if (distance > 24.0 || !has_line_of_sight(pd, pd->player.bpos, medkit->pos))
        return (false);
    inv_det = 1.0 / (pd->player.camera_plane.dir.x * pd->player.bdir.y
            - pd->player.bdir.x * pd->player.camera_plane.dir.y);
    transform.x = -inv_det * (pd->player.bdir.y * rel_pos.x
            - pd->player.bdir.x * rel_pos.y);
    transform.y = inv_det * (-pd->player.camera_plane.dir.y * rel_pos.x
            + pd->player.camera_plane.dir.x * rel_pos.y);
    if (transform.y <= 0)
        return (false);
    out->medkit = medkit;
    out->distance = distance;
    out->transform = transform;
    out->sprite_screen_x = (int)((WIDTH / 2) * (1 + transform.x / transform.y));
    out->sprite_height = abs((int)(HEIGHT / transform.y)) * medkit->size_scale;
    out->sprite_width = abs((int)(HEIGHT / transform.y)) * medkit->size_scale;
    return (true);
}
