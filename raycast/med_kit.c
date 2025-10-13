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

void draw_medkits(t_parsed_data *pd)
{
    int horizon = HEIGHT / 2 + (int)pd->player.pitch;
    
    typedef struct {
        t_med_kit *medkit;
        double distance;
        t_bpos transform;
        int sprite_screen_x;
        int sprite_height;
        int sprite_width;
    } t_medkit_draw_data;
    
    t_medkit_draw_data draw_data[pd->max_medkits];
    int draw_count = 0;

    for (int i = 0; i < pd->medkit_count; i++)
    {
        if (pd->medkits[i].picked)
            continue;
            
        t_med_kit *medkit = &pd->medkits[i];
        
        t_bpos rel_pos;
        rel_pos.x = medkit->pos.x - pd->player.bpos.x;
        rel_pos.y = medkit->pos.y - pd->player.bpos.y;
        
        double distance = sqrt(rel_pos.x * rel_pos.x + rel_pos.y * rel_pos.y);

        if (distance > 24.0 || !has_line_of_sight(pd, pd->player.bpos, medkit->pos))
            continue;
            
        double inv_det = 1.0 / (pd->player.camera_plane.dir.x * pd->player.bdir.y
                - pd->player.bdir.x * pd->player.camera_plane.dir.y);
        t_bpos transform;
        transform.x = -inv_det * (pd->player.bdir.y * rel_pos.x
                - pd->player.bdir.x * rel_pos.y);
        transform.y = inv_det * (-pd->player.camera_plane.dir.y * rel_pos.x
                + pd->player.camera_plane.dir.x * rel_pos.y);
                
        if (transform.y <= 0)
            continue;
            

        draw_data[draw_count].medkit = medkit;
        draw_data[draw_count].distance = distance;
        draw_data[draw_count].transform = transform;
        draw_data[draw_count].sprite_screen_x = (int)((WIDTH / 2) * (1 + transform.x / transform.y));
        draw_data[draw_count].sprite_height = abs((int)(HEIGHT / transform.y)) * medkit->size_scale;
        draw_data[draw_count].sprite_width = abs((int)(HEIGHT / transform.y)) * medkit->size_scale;
        
        draw_count++;
    }
    
    for (int i = 0; i < draw_count - 1; i++)
    {
        for (int j = i + 1; j < draw_count; j++)
        {
            if (draw_data[i].distance < draw_data[j].distance)
            {
                t_medkit_draw_data temp = draw_data[i];
                draw_data[i] = draw_data[j];
                draw_data[j] = temp;
            }
        }
    }

    for (int i = 0; i < draw_count; i++)
    {
        t_med_kit *medkit = draw_data[i].medkit;
        double distance = draw_data[i].distance;
        t_bpos transform = draw_data[i].transform;
        int sprite_screen_x = draw_data[i].sprite_screen_x;
        int sprite_height = draw_data[i].sprite_height;
        int sprite_width = draw_data[i].sprite_width;
        
        int vertical_offset_pixels = (int)(sprite_height * medkit->vertical_offset);
        
        int draw_start_y = -sprite_height / 2 + horizon + vertical_offset_pixels;
        if (draw_start_y < 0) draw_start_y = 0;
        int draw_end_y = sprite_height / 2 + horizon + vertical_offset_pixels;
        if (draw_end_y >= HEIGHT) draw_end_y = HEIGHT - 1;
        
        int draw_start_x = -sprite_width / 2 + sprite_screen_x;
        if (draw_start_x < 0) draw_start_x = 0;
        int draw_end_x = sprite_width / 2 + sprite_screen_x;
        if (draw_end_x >= WIDTH) draw_end_x = WIDTH - 1;
        

        for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
        {
            for (int y = draw_start_y; y < draw_end_y; y++)
            {
                int tex_x = (int)((stripe - (-sprite_width / 2 + sprite_screen_x)) * 
                         (double)medkit->img.img->width / (double)sprite_width);
                int tex_y = (int)((y - (-sprite_height / 2 + horizon + vertical_offset_pixels)) * 
                         (double)medkit->img.img->height / (double)sprite_height);
                
                t_tex_sample sample = sample_texture_pixel(medkit->img.img, tex_x, tex_y);
                if (sample.ok && sample.alpha != 0)
                {
                    mlx_put_pixel(pd->screen, stripe, y,
                        shade_color(sample.color, distance, 0.15));
                }
            }
        }
    }
}
