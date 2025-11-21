/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 01:12:42 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/21 16:39:10 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

bool	attempt_one_step(t_enemy *enemy, t_parsed_data *pd,
		t_bpos dir, t_move_ctx *ctx)
{
	double	nx;
	double	ny;

	nx = enemy->b_pos.x + ctx->step_x;
	ny = enemy->b_pos.y + ctx->step_y;
	if (try_axis_moves(enemy, pd, nx, ny))
		return (true);
	if (try_alternative_directions(enemy, pd, dir, ctx->alt_step))
	{
		ctx->moved = true;
		ctx->s = ctx->steps;
		return (true);
	}
	ctx->s = ctx->steps;
	return (false);
}

bool	perform_move_steps(t_enemy *enemy, t_parsed_data *pd,
		t_bpos dir, double speed)
{
	t_move_ctx	ctx;

	ctx.steps = 2;
	ctx.s = 0;
	ctx.step_x = dir.x * speed / (double)ctx.steps;
	ctx.step_y = dir.y * speed / (double)ctx.steps;
	ctx.alt_step = speed / (double)ctx.steps;
	ctx.moved = false;
	while (ctx.s < ctx.steps)
	{
		if (attempt_one_step(enemy, pd, dir, &ctx))
			ctx.moved = true;
		if (ctx.s < ctx.steps)
			ctx.s++;
	}
	return (ctx.moved);
}

// se

bool	move_towards_target(t_enemy *enemy, t_parsed_data *pd,
		t_bpos target, double speed)
{
	t_bpos	dir;
	double	len;

	if (!enemy || !pd)
		return (false);
	dir.x = target.x - enemy->b_pors.x;
	dir.y = target.y - enemy->b_pos.y;
	len = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len <= 1e-9)
		return (false);
	dir.x /= len;
	dir.y /= len;
	if (perform_move_steps(enemy, pd, dir, speed))
	{
		// play movement sound for each enemy type and based on distance from player using 
		//void    play_enemy_sound_3d(t_parsed_data *pd, t_enemy *e, const char *path)
		// play_enemy_walk_sound(pd, enemy);
		dir.x = target.x - enemy->b_pos.x;
		dir.y = target.y - enemy->b_pos.y;
		len = sqrt(dir.x * dir.x + dir.y * dir.y);
		if (len > 1e-9)
		{
			enemy->dir.x = dir.x / len;
			enemy->dir.y = dir.y / len;
		}
		return (true);
	}
	return (false);
}

void	handle_patrol_attempt(t_enemy *enemy, t_parsed_data *pd,
		t_bpos target, int *stuck_counter)
{
	if (!move_towards_target(enemy, pd, target, enemy->patrol_speed))
	{
		(*stuck_counter)++;
		if (*stuck_counter > 10)
		{
			enemy->patrol_target_timer = 0;
		}
		else
		{
			if (!try_alternative_directions(enemy, pd,
					(t_bpos){target.x - enemy->b_pos.x,
					target.y - enemy->b_pos.y},
				enemy->patrol_speed))
			{
				change_enemy_direction(enemy);
			}
		}
	}
	else
	{
		*stuck_counter = 0;
	}
}

void	handle_patrol_state(t_enemy_ctx *ctx)
{
	if (ctx->distance <= CHASE_DISTANCE && ctx->visible)
		ctx->enemy->state = ENEMY_CHASE;
	else
		perform_patrol_movement(ctx->enemy, ctx->pd);
}
