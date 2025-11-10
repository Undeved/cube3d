/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 05:37:12 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/10 08:00:52 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	player_rotation(t_parsed_data *pd)
{
	int		delta_x;
	double	old_x;
	double	old_y;
	double	angle;

	old_x = pd->player.bdir.x;
	old_y = pd->player.bdir.y;
	if (pd->keys.pressed[MLX_KEY_RIGHT])
	{
		pd->player.bdir.x = old_x * cos(ROT_SPEED) - old_y * sin(ROT_SPEED);
		pd->player.bdir.y = old_x * sin(ROT_SPEED) + old_y * cos(ROT_SPEED);
	}
	if (pd->keys.pressed[MLX_KEY_LEFT])
	{
		pd->player.bdir.x = old_x * cos(-ROT_SPEED) - old_y * sin(-ROT_SPEED);
		pd->player.bdir.y = old_x * sin(-ROT_SPEED) + old_y * cos(-ROT_SPEED);
	}
	delta_x = pd->mouse.x - (WIDTH / 2);
	if (delta_x != 0)
	{
		angle = delta_x * MOUSE_SENSITIVITY;
		pd->player.bdir.x = old_x * cos(angle) - old_y * sin(angle);
		pd->player.bdir.y = old_x * sin(angle) + old_y * cos(angle);
	}
	mlx_set_mouse_pos(pd->mlx, WIDTH / 2, HEIGHT / 2);
}

static bool	is_collision(char **map_grid, double x, double y)
{
	if (map_grid[(int)y][(int)x] == '1' || map_grid[(int)y][(int)x] == 'D')
		return (true);
	if (map_grid[(int)y][(int)(x + COLLISION)] == '1'
		|| map_grid[(int)y][(int)(x - COLLISION)] == '1')
		return (true);
	if (map_grid[(int)y][(int)(x + COLLISION)] == 'D'
		|| map_grid[(int)y][(int)(x - COLLISION)] == 'D')
		return (true);
	if (map_grid[(int)(y + COLLISION)][(int)x] == '1'
		|| map_grid[(int)(y - COLLISION)][(int)x] == '1')
		return (true);
	if (map_grid[(int)(y + COLLISION)][(int)x] == 'D'
		|| map_grid[(int)(y - COLLISION)][(int)x] == 'D')
		return (true);
	return (false);
}

static void	forward_backward(t_parsed_data *pd)
{
	double	move_speed;

	move_speed = get_move_speed(pd, SPEED);
	if (pd->keys.pressed[MLX_KEY_W])
	{
		pd->player.new_pos.x += pd->player.bdir.x * move_speed;
		pd->player.new_pos.y += pd->player.bdir.y * move_speed;
		if (!is_collision(pd->map_grid,
				pd->player.new_pos.x, pd->player.bpos.y))
			pd->player.bpos.x = pd->player.new_pos.x;
		if (!is_collision(pd->map_grid,
				pd->player.bpos.x, pd->player.new_pos.y))
			pd->player.bpos.y = pd->player.new_pos.y;
	}
	if (pd->keys.pressed[MLX_KEY_S])
	{
		pd->player.new_pos.x -= pd->player.bdir.x * move_speed;
		pd->player.new_pos.y -= pd->player.bdir.y * move_speed;
		if (!is_collision(pd->map_grid,
				pd->player.new_pos.x, pd->player.bpos.y))
			pd->player.bpos.x = pd->player.new_pos.x;
		if (!is_collision(pd->map_grid,
				pd->player.bpos.x, pd->player.new_pos.y))
			pd->player.bpos.y = pd->player.new_pos.y;
	}
}

static void	strafe(t_parsed_data *pd)
{
	double	move_speed;

	move_speed = get_move_speed(pd, STRAFE_SPEED);
	if (pd->keys.pressed[MLX_KEY_A])
	{
		pd->player.new_pos.x += pd->player.bdir.y * move_speed;
		pd->player.new_pos.y += -pd->player.bdir.x * move_speed;
		if (!is_collision(pd->map_grid,
				pd->player.new_pos.x, pd->player.bpos.y))
			pd->player.bpos.x = pd->player.new_pos.x;
		if (!is_collision(pd->map_grid,
				pd->player.bpos.x, pd->player.new_pos.y))
			pd->player.bpos.y = pd->player.new_pos.y;
	}
	if (pd->keys.pressed[MLX_KEY_D])
	{
		pd->player.new_pos.x += -pd->player.bdir.y * move_speed;
		pd->player.new_pos.y += pd->player.bdir.x * move_speed;
		if (!is_collision(pd->map_grid,
				pd->player.new_pos.x, pd->player.bpos.y))
			pd->player.bpos.x = pd->player.new_pos.x;
		if (!is_collision(pd->map_grid,
				pd->player.bpos.x, pd->player.new_pos.y))
			pd->player.bpos.y = pd->player.new_pos.y;
	}
}

void	player_movement(t_parsed_data *pd)
{
	pd->player.new_pos.x = pd->player.bpos.x;
	pd->player.new_pos.y = pd->player.bpos.y;
	forward_backward(pd);
	strafe(pd);
}
