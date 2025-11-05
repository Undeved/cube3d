#include "../../cube.h"

static void delete_medkit_textures(t_parsed_data *pd)
{
    int i;

    if (pd->medkit.img)
        mlx_delete_image(pd->mlx, pd->medkit.img);
    if (pd->medkit.txtr)
        mlx_delete_texture(pd->medkit.txtr);
    if (!pd->medkits)
        return ;
    i = 0;
    while (i < MAX_ENEMIES)
    {
        if (pd->medkits[i].img.img)
            mlx_delete_image(pd->mlx, pd->medkits[i].img.img);
        if (pd->medkits[i].img.txtr)
            mlx_delete_texture(pd->medkits[i].img.txtr);
        i++;
    }
}

static void mlx_delete_image_set_null(mlx_t *mlx, mlx_image_t **img)
{
    mlx_delete_image(mlx, *img);
    *img = NULL;
}

static void free_shared_attack(t_parsed_data *pd)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (pd->sh.skin_walker_walk[i].img)
            mlx_delete_image_set_null(pd->mlx, &pd->sh.skin_walker_walk[i].img);
        if (pd->sh.skin_walker_attack[i].img)
            mlx_delete_image_set_null(pd->mlx, &pd->sh.skin_walker_attack[i].img);
        if (pd->sh.memory_leak_walk[i].img)
            mlx_delete_image_set_null(pd->mlx, &pd->sh.memory_leak_walk[i].img);
        if (pd->sh.memory_leak_attack[i].img)
            mlx_delete_image_set_null(pd->mlx, &pd->sh.memory_leak_attack[i].img);
        if (pd->sh.segv_walk[i].img)
            mlx_delete_image_set_null(pd->mlx, &pd->sh.segv_walk[i].img);
        if (pd->sh.segv_attack[i].img)
            mlx_delete_image_set_null(pd->mlx, &pd->sh.segv_attack[i].img);
        i++;
    }
}

static void free_sh_imgs(t_parsed_data *pd)
{
    int i;

    if (!pd->sh.initialized)
        return;
    if (pd->sh.skin_walker_default.img)
        mlx_delete_image_set_null(pd->mlx, &pd->sh.skin_walker_default.img);
    if (pd->sh.memory_leak_default.img)
        mlx_delete_image_set_null(pd->mlx, &pd->sh.memory_leak_default.img);
    if (pd->sh.segv_default.img)
        mlx_delete_image_set_null(pd->mlx, &pd->sh.segv_default.img);
    free_shared_attack(pd);
    i = 0;
    while (i < 2)
    {
        if (pd->sh.skin_walker_death[i].img)
            mlx_delete_image_set_null(pd->mlx, &pd->sh.skin_walker_death[i].img);
        if (pd->sh.memory_leak_death[i].img)
            mlx_delete_image_set_null(pd->mlx, &pd->sh.memory_leak_death[i].img);
        if (pd->sh.segv_death[i].img)
            mlx_delete_image_set_null(pd->mlx, &pd->sh.segv_death[i].img);
        i++;
    }
}


void delete_all_textures(t_parsed_data *pd)
{
    if (!pd)
        return ;
    if (!pd->mlx)
        return ;
    delete_player_textures(pd);
    delete_screen_and_map(pd);
    delete_main_menu_textures(pd);
    delete_characters_ui_textures(pd);
    delete_game_ui_textures(pd);
    free_sh_imgs(pd);
    delete_door_wall_textures(pd);
    delete_medkit_textures(pd);
}
