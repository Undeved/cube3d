/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 01:13:25 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 03:22:25 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	calculate_draw_bounds(t_enemy_draw_data *curr, int horizon,
		t_draw_bounds *b)
{
	b->orig_draw_start_y = -curr->sprite_height / 2 + horizon;
	b->orig_draw_start_x = -curr->sprite_width / 2 + curr->sprite_screen_x;
	b->draw_start_y = b->orig_draw_start_y;
	if (b->draw_start_y < 0)
		b->draw_start_y = 0;
	b->draw_end_y = curr->sprite_height / 2 + horizon;
	if (b->draw_end_y >= HEIGHT)
		b->draw_end_y = HEIGHT - 1;
	b->draw_start_x = b->orig_draw_start_x;
	if (b->draw_start_x < 0)
		b->draw_start_x = 0;
	b->draw_end_x = curr->sprite_width / 2 + curr->sprite_screen_x;
	if (b->draw_end_x >= WIDTH)
		b->draw_end_x = WIDTH - 1;
}

void	calculate_direction_to_player(t_enemy *enemy, t_bpos player_pos,
		t_bpos *direction)
{
	double	length;

	direction->x = player_pos.x - enemy->b_pos.x;
	direction->y = player_pos.y - enemy->b_pos.y;
	length = sqrt(direction->x * direction->x + direction->y * direction->y);
	if (length > 0)
	{
		direction->x /= length;
		direction->y /= length;
	}
}

int	find_current_direction(t_enemy *enemy, double directions[4][2])
{
	int	i;
	int	current_dir_index;

	i = 0;
	current_dir_index = -1;
	while (i < 4)
	{
		if (fabs(enemy->dir.x - directions[i][0]) < 0.1
			&& fabs(enemy->dir.y - directions[i][1]) < 0.1)
		{
			current_dir_index = i;
			break ;
		}
		i++;
	}
	return (current_dir_index);
}

void	update_attack_animation(t_enemy *enemy)
{
	enemy->attack_anim_counter++;
	if (enemy->attack_anim_counter >= ENEMY_ANIM_RATE / 2)
	{
		enemy->attack_anim_counter = 0;
		enemy->anim_frame = (enemy->anim_frame + 1) % 3;
		if (enemy->anim_frame == 0)
			enemy->anim_img = enemy->attack1->img;
		else if (enemy->anim_frame == 1)
			enemy->anim_img = enemy->attack2->img;
		else
		{
			enemy->anim_img = enemy->attack3->img;
			if (enemy->attack_cooldown <= 0)
				enemy->is_attacking = false;
		}
	}
}

int	is_valid_enemy(t_enemy_draw_data *data)
{
	if (data->enemy->is_dying)
		return (0);
	if (data->enemy->dead && !data->enemy->is_dying)
		return (0);
	return (1);
}
