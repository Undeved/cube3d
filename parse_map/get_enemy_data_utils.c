/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_enemy_data_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 05:10:18 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/08 05:14:44 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_rand(void)
{
	struct timeval			tv;
	static unsigned long	random = 0;

	gettimeofday(&tv, 0);
	if (random == 0)
		random = tv.tv_sec + tv.tv_usec;
	random = (1103515245 * random + 12345) & 2147483647;
	return ((int)(random % (RAND_MAX)));
}

static void	y_z_data(int x, int y, char c, t_enemy *curr_enemy)
{
	if (c == 'Y')
	{
		curr_enemy->type = MEMORY_LEAK;
		curr_enemy->patrol_speed = MEMORY_LEAK_PATROL_SPEED;
		curr_enemy->chase_speed = MEMORY_LEAK_CHASE_SPEED;
		curr_enemy->pos.x = x;
		curr_enemy->pos.y = y;
		curr_enemy->skin.img = NULL;
		curr_enemy->dead = false;
		curr_enemy->damage = MEMORY_LEAK_DAMAGE;
		curr_enemy->health = MEMORY_LEAK_HEALTH;
	}
	else if (c == 'Z')
	{
		curr_enemy->type = SEGV;
		curr_enemy->patrol_speed = SEGV_PATROL_SPEED;
		curr_enemy->chase_speed = SEGV_CHASE_SPEED;
		curr_enemy->pos.x = x;
		curr_enemy->pos.y = y;
		curr_enemy->skin.img = NULL;
		curr_enemy->dead = false;
		curr_enemy->damage = SEGV_DAMAGE;
		curr_enemy->health = SEGV_HEALTH;
	}
}

static void	init_directions(t_bpos directions[4])
{
	directions[0].x = 0.0;
	directions[0].y = 1.0;
	directions[1].x = 1.0;
	directions[1].y = 0.0;
	directions[2].x = 0.0;
	directions[2].y = -1.0;
	directions[3].x = -1.0;
	directions[3].y = 0.0;
}

void	scrap_enemy_data(int x, int y, char c, t_enemy *curr_enemy)
{
	t_bpos	directions[4];
	int		dir_index;

	curr_enemy->b_pos.x = (double)x + 0.5;
	curr_enemy->b_pos.y = (double)y + 0.5;
	curr_enemy->patrol_origin = curr_enemy->b_pos;
	init_directions(directions);
	dir_index = ft_rand() % 4;
	curr_enemy->dir.x = directions[dir_index].x;
	curr_enemy->dir.y = directions[dir_index].y;
	curr_enemy->state = ENEMY_PATROL;
	if (c == 'X')
	{
		curr_enemy->type = FT_SKIN_WALKER;
		curr_enemy->patrol_speed = SKIN_WALKER_PATROL_SPEED;
		curr_enemy->chase_speed = SKIN_WALKER_CHASE_SPEED;
		curr_enemy->pos.x = x;
		curr_enemy->pos.y = y;
		curr_enemy->skin.img = NULL;
		curr_enemy->dead = false;
		curr_enemy->damage = SKIN_WALKER_DAMAGE;
		curr_enemy->health = SKIN_WALKER_HEALTH;
	}
	y_z_data(x, y, c, curr_enemy);
}
