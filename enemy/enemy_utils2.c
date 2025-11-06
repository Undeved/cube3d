/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 01:13:11 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 03:33:36 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	smart_chase_player(t_enemy *enemy, t_bpos player_pos, double speed,
		t_parsed_data *pd)
{
	t_bpos	direction;
	t_bpos	new_pos;
	bool	moved;

	calculate_direction_to_player(enemy, player_pos, &direction);
	new_pos.x = enemy->b_pos.x + direction.x * speed;
	new_pos.y = enemy->b_pos.y + direction.y * speed;
	if (is_valid_move_position_circle_global(pd, new_pos.x, new_pos.y)
		&& !is_diagonal_gap(pd, enemy->b_pos, new_pos))
	{
		enemy->b_pos = new_pos;
		enemy->dir.x = direction.x;
		enemy->dir.y = direction.y;
		return ;
	}
	moved = try_alternative_directions(enemy, pd, direction, speed);
	if (!moved)
		enemy->state = ENEMY_RETURN;
}

double	dist2(t_bpos a, t_bpos b)
{
	double	dx;
	double	dy;

	dx = a.x - b.x;
	dy = a.y - b.y;
	return (dx * dx + dy * dy);
}

void	perform_patrol_movement(t_enemy *enemy, t_parsed_data *pd)
{
	t_bpos		target;
	static int	stuck_counter = 0;

	if (!enemy || !pd)
		return ;
	if (enemy->patrol_target_timer <= 0
		|| dist2(enemy->b_pos,
			enemy->patrol_target) <= (PATROL_REACHED_EPS * PATROL_REACHED_EPS))
	{
		if (!choose_random_patrol_target(enemy, pd))
		{
			change_enemy_direction(enemy);
			enemy->patrol_target_timer = 30;
		}
		stuck_counter = 0;
	}
	target = enemy->patrol_target;
	handle_patrol_attempt(enemy, pd, target, &stuck_counter);
	if (enemy->patrol_target_timer > 0)
		enemy->patrol_target_timer--;
}

bool	is_diagonal_gap(t_parsed_data *pd, t_bpos from, t_bpos to)
{
	int	from_x;
	int	from_y;
	int	to_x;
	int	to_y;

	from_x = (int)from.x;
	from_y = (int)from.y;
	to_x = (int)to.x;
	to_y = (int)to.y;
	if (from_x != to_x && from_y != to_y)
	{
		if (pd->map_grid[from_y][to_x] == '1'
				&& pd->map_grid[to_y][from_x] == '1')
			return (true);
	}
	return (false);
}

bool	try_axis_moves(t_enemy *enemy, t_parsed_data *pd,
		double nx, double ny)
{
	if (is_valid_move_position_circle_global(pd, nx, ny)
		&& !is_diagonal_gap(pd, enemy->b_pos, (t_bpos){nx, ny}))
	{
		enemy->b_pos.x = nx;
		enemy->b_pos.y = ny;
		return (true);
	}
	if (is_valid_move_position_circle_global(pd, nx, enemy->b_pos.y))
	{
		enemy->b_pos.x = nx;
		return (true);
	}
	if (is_valid_move_position_circle_global(pd, enemy->b_pos.x, ny))
	{
		enemy->b_pos.y = ny;
		return (true);
	}
	return (false);
}
