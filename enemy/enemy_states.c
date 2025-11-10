/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 01:13:38 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/10 15:29:44 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	handle_chase_state(t_parsed_data *pd, t_enemy *enemy, int i,
		double distance)
{
	(void)i;
	if (!has_line_of_sight(pd, enemy->b_pos, pd->player.bpos))
	{
		enemy->state = ENEMY_RETURN;
		return ;
	}
	if (distance > LOSE_DISTANCE)
		enemy->state = ENEMY_RETURN;
	else if (distance <= ATTACK_DISTANCE)
	{
		enemy->state = ENEMY_ATTACK;
		pd->player.health -= enemy->damage;
		if (pd->player.health <= 0)
		{
			pd->player.health = 0;
			pd->player.last_killer = enemy;
		}
	}
	else
		smart_chase_player(enemy, pd->player.bpos, enemy->chase_speed, pd);
}

static void	perform_enemy_attack(t_parsed_data *pd, t_enemy *enemy)
{
	if (enemy->attack_cooldown <= 0)
	{
		enemy->is_attacking = true;
		enemy->anim_frame = 0;
		enemy->attack_anim_counter = 0;
		pd->player.health -= enemy->damage;
		if (pd->player.health <= 0)
		{
			pd->player.health = 0;
			pd->player.last_killer = enemy;
		}
		enemy->attack_cooldown = 20;
	}
	else
		enemy->attack_cooldown--;
}

void	handle_attack_state(t_parsed_data *pd, t_enemy *enemy, int i,
		double distance)
{
	(void)i;
	if (!has_line_of_sight(pd, enemy->b_pos, pd->player.bpos))
	{
		enemy->state = ENEMY_RETURN;
		enemy->attack_cooldown = 0;
		enemy->is_attacking = false;
		return ;
	}
	if (distance > ATTACK_DISTANCE)
	{
		if (distance <= LOSE_DISTANCE)
			enemy->state = ENEMY_CHASE;
		else
			enemy->state = ENEMY_RETURN;
		enemy->attack_cooldown = 0;
		enemy->is_attacking = false;
	}
	else
		perform_enemy_attack(pd, enemy);
}

void	handle_return_state(t_parsed_data *pd, t_enemy *enemy, int i)
{
	(void)i;
	if (return_to_patrol(enemy, pd))
		enemy->state = ENEMY_PATROL;
}

void	handle_enemy_state(t_enemy_ctx *ctx)
{
	if (ctx->enemy->is_dying)
		return ;
	if (ctx->enemy->state == ENEMY_PATROL)
		handle_patrol_state(ctx);
	else if (ctx->enemy->state == ENEMY_CHASE)
		handle_chase_state(ctx->pd, ctx->enemy, ctx->index, ctx->distance);
	else if (ctx->enemy->state == ENEMY_ATTACK)
		handle_attack_state(ctx->pd, ctx->enemy, ctx->index, ctx->distance);
	else if (ctx->enemy->state == ENEMY_RETURN)
		handle_return_state(ctx->pd, ctx->enemy, ctx->index);
}
