#include "../cube.h"

void update_walk_animation(t_enemy *enemy)
{
    enemy->anim_counter++;
    if (enemy->anim_counter >= ENEMY_ANIM_RATE)
    {
        enemy->anim_counter = 0;
        enemy->anim_frame = (enemy->anim_frame + 1) % 3;
        if (enemy->anim_frame == 0)
            enemy->anim_img = enemy->walk1->img;
        else if (enemy->anim_frame == 1)
            enemy->anim_img = enemy->walk2->img;
        else
            enemy->anim_img = enemy->walk3->img;
    }
}

void update_enemy_animations(t_enemy *enemy)
{
    if (enemy->state == ENEMY_ATTACK && enemy->is_attacking)
        update_attack_animation(enemy);
    else if (enemy->state == ENEMY_PATROL || enemy->state == ENEMY_CHASE)
        update_walk_animation(enemy);
    else
    {
        enemy->anim_img = enemy->skin.img;
        enemy->anim_frame = 0;
        enemy->anim_counter = 0;
        enemy->is_attacking = false;
        enemy->attack_anim_counter = 0;
    }
}

void update_single_enemy(t_parsed_data *pd, int i)
{
    t_enemy     *enemy;
    double      distance;
    bool        visible;
    t_enemy_ctx ctx;

    ctx.index = i;
    enemy = &pd->enemies[ctx.index];
    if (enemy->dead || enemy->is_dying)
        return ;
    distance = calculate_distance_to_player(enemy, pd);
    visible = has_line_of_sight(pd, enemy->b_pos, pd->player.bpos);
    ctx.pd = pd;
    ctx.enemy = enemy;
    ctx.distance = distance;
    ctx.visible = visible;
    handle_enemy_state(&ctx);
    if (enemy->is_highlighted)
    {
        if (--enemy->highlight_timer <= 0)
        {
            enemy->is_highlighted = false;
            enemy->highlight_timer = 0;
        }
    }
    update_enemy_animations(enemy);
}
bool all_enemies_dead(t_parsed_data *pd)
{
    int i;

    if (!pd || !pd->enemies || pd->enemy_count == 0)
        return (false);

    i = 0;
    while (i < pd->enemy_count)
    {
        if (!pd->enemies[i].dead)
            return (false);
        i++;
    }
    return (true);
}

void show_game_won_if_needed(t_parsed_data *pd)
{
    if (!pd)
        return ;
    if (pd->game_ui.game_won.img && pd->game_ui.game_won.img->enabled)
        return ;
    if (all_enemies_dead(pd))
        pd->player.has_won = true;
}

void update_enemies(t_parsed_data *pd)
{
    int i;

    if (!pd->enemies || pd->enemy_count == 0)
        return ;
    i = 0;
    while (i < pd->enemy_count)
    {
        update_single_enemy(pd, i);
        i++;
    }
    show_game_won_if_needed(pd);
}
