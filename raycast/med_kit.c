#include "../cube.h"

void spawn_medkit(t_parsed_data *pd, t_bpos pos, t_enemy_type type)
{
    if (pd->medkit_count >= pd->max_medkits)
        return;
    
    t_med_kit *medkit = &pd->medkits[pd->medkit_count];
    
    medkit->pos = pos;
    medkit->picked = false;
    
    if (type == FT_SKIN_WALKER)
    {
        medkit->hp_trmat_oussmac = 20;
        medkit->size_scale = 0.5f;
        medkit->vertical_offset = 1.1f;
    }
    else if (type == MEMORY_LEAK)
    {
        medkit->hp_trmat_oussmac = 30;
        medkit->size_scale = 0.5f;
          medkit->vertical_offset = 1.1f;
    }
    else if (type == SEGV)
    {
        medkit->hp_trmat_oussmac = 40;
        medkit->size_scale = 0.5f;
         medkit->vertical_offset = 1.1f;
    }
    else
    {
        medkit->hp_trmat_oussmac = 25;
        medkit->size_scale = 0.5f;
        medkit->vertical_offset = 1.1f;
    }
    
    medkit->img = pd->medkits[0].img;
    
    pd->medkit_count++;
}

void check_medkit_pickup(t_parsed_data *pd)
{
    int i = 0;
    int picked_count = 0;
    
    while (i < pd->medkit_count)
    {
        if (pd->medkits[i].picked)
        {

            if (i < pd->medkit_count - 1)
                pd->medkits[i] = pd->medkits[pd->medkit_count - 1];
            pd->medkit_count--;
            picked_count++;
            continue;
        }
        double dx = pd->medkits[i].pos.x - pd->player.bpos.x;
        double dy = pd->medkits[i].pos.y - pd->player.bpos.y;
        double distance = sqrt(dx * dx + dy * dy);
        if (distance < 0.8) 
        {
            int old_health = pd->player.health;
            pd->player.health += pd->medkits[i].hp_trmat_oussmac;
            if (pd->player.health > PLAYER_HEALTH)
                pd->player.health = PLAYER_HEALTH;
            pd->medkits[i].picked = true;
            picked_count++;
            
            continue;
        }
        
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

void collect_medkits(t_parsed_data *pd, t_medkit_draw_data *draw_data, int *draw_count)
{
    int i;
    int dc;
    int horizon;

    i = 0;
    dc = 0;
    horizon = HEIGHT / 2 + (int)pd->player.pitch;
    while (i < pd->medkit_count)
    {
        if (!pd->medkits[i].picked)
        {
            if (medkit_visible(pd, &pd->medkits[i], &draw_data[dc]))
            {
                draw_data[dc].v_offset_pixels = (int)(draw_data[dc].sprite_height
                                                  * draw_data[dc].medkit->vertical_offset);
                draw_data[dc].draw_start_y = -draw_data[dc].sprite_height / 2
                                            + horizon + draw_data[dc].v_offset_pixels;
                if (draw_data[dc].draw_start_y < 0)
                    draw_data[dc].draw_start_y = 0;
                draw_data[dc].draw_end_y = draw_data[dc].sprite_height / 2
                                          + horizon + draw_data[dc].v_offset_pixels;
                if (draw_data[dc].draw_end_y >= HEIGHT)
                    draw_data[dc].draw_end_y = HEIGHT - 1;
                draw_data[dc].draw_start_x = -draw_data[dc].sprite_width / 2
                                            + draw_data[dc].sprite_screen_x;
                if (draw_data[dc].draw_start_x < 0)
                    draw_data[dc].draw_start_x = 0;
                draw_data[dc].draw_end_x = draw_data[dc].sprite_width / 2
                                          + draw_data[dc].sprite_screen_x;
                if (draw_data[dc].draw_end_x >= WIDTH)
                    draw_data[dc].draw_end_x = WIDTH - 1;
                dc++;
            }
        }
        i++;
    }
    *draw_count = dc;
}

void sort_medkits_by_distance(t_medkit_draw_data *draw_data, int draw_count)
{
    int i;
    int j;
    t_medkit_draw_data tmp;

    i = 0;
    while (i < draw_count - 1)
    {
        j = i + 1;
        while (j < draw_count)
        {
            if (draw_data[i].distance < draw_data[j].distance)
            {
                tmp = draw_data[i];
                draw_data[i] = draw_data[j];
                draw_data[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void draw_single_medkit(t_parsed_data *pd, t_medkit_draw_data *entry)
{
    t_med_kit *medkit;
    int sprite_width;
    int sprite_height;
    int stripe_count;

    medkit = entry->medkit;
    sprite_width = entry->sprite_width;
    sprite_height = entry->sprite_height;
    entry->stripe = entry->draw_start_x;
    stripe_count = entry->draw_end_x;
    while (entry->stripe < stripe_count)
    {
        entry->y = entry->draw_start_y;
        while (entry->y < entry->draw_end_y)
        {
            entry->tex_x = (int)((entry->stripe - (-sprite_width / 2 + entry->sprite_screen_x))
                         * (double)medkit->img.img->width / (double)sprite_width);
            entry->tex_y = (int)((entry->y - (-sprite_height / 2
                         + (HEIGHT / 2 + (int)pd->player.pitch) + entry->v_offset_pixels))
                         * (double)medkit->img.img->height / (double)sprite_height);
            entry->tmp_sample = sample_texture_pixel(medkit->img.img, entry->tex_x, entry->tex_y);
            if (entry->tmp_sample.ok && entry->tmp_sample.alpha != 0)
                mlx_put_pixel(pd->screen, entry->stripe, entry->y,
                    shade_color(entry->tmp_sample.color, entry->distance, 0.15));
            entry->y++;
        }
        entry->stripe++;
    }
}

void draw_medkits(t_parsed_data *pd)
{
    t_medkit_draw_data draw_data[pd->max_medkits];
    int draw_count;
    int i;

    draw_count = 0;
    collect_medkits(pd, draw_data, &draw_count);
    if (draw_count > 1)
        sort_medkits_by_distance(draw_data, draw_count);
    i = 0;
    while (i < draw_count)
    {
        draw_single_medkit(pd, &draw_data[i]);
        i++;
    }
}


