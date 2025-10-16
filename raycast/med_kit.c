#include "../cube.h"

void calculate_medkit_draw_data(t_medkit_draw_data *draw_data, int dc, int horizon)
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
                calculate_medkit_draw_data(draw_data, dc, horizon);
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

    medkit = entry->medkit;
    medkit->sprite_width = entry->sprite_width;
    medkit->sprite_height = entry->sprite_height;
    entry->stripe = entry->draw_start_x;
    medkit->stripe_count = entry->draw_end_x;
    while (entry->stripe < medkit->stripe_count)
    {
        entry->y = entry->draw_start_y;
        while (entry->y < entry->draw_end_y)
        {
            entry->tex_x = (int)((entry->stripe - (-medkit->sprite_width / 2 + entry->sprite_screen_x))
                         * (double)medkit->img.img->width / (double)medkit->sprite_width);
            entry->tex_y = (int)((entry->y - (-medkit->sprite_height / 2
                         + (HEIGHT / 2 + (int)pd->player.pitch) + entry->v_offset_pixels))
                         * (double)medkit->img.img->height / (double)medkit->sprite_height);
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
