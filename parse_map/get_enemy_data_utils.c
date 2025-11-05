#include "../cube.h"

int	ft_rand(void)
{
	struct timeval	tv;
	static unsigned long	random = 0;

	gettimeofday(&tv, 0);
	if (random == 0)
		random = tv.tv_sec + tv.tv_usec;
	random = (1103515245 * random + 12345) & 2147483647;
	return ((int)(random % (RAND_MAX )));
}


static void y_z_data(int x, int y, char c, t_enemy *curr_enemy)
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

void scrap_enemy_data(int x, int y, char c, t_enemy *curr_enemy)
{
    double  directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int     dir_index;
    
    curr_enemy->b_pos.x = (double)x + 0.5;
    curr_enemy->b_pos.y = (double)y + 0.5;
    curr_enemy->patrol_origin = curr_enemy->b_pos;
    dir_index = ft_rand() % 4;
    curr_enemy->dir.x = directions[dir_index][0];
    curr_enemy->dir.y = directions[dir_index][1];
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
