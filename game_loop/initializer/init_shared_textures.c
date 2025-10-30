#include "../../cube.h"

static void load_shared_animation_frame(t_parsed_data *pd, t_raw_img *frames, char **paths, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (frames[i].txtr == NULL)
        {
            frames[i].txtr = mlx_load_png(paths[i]);
            if (frames[i].txtr == NULL)
            {
                print_error("Error\nEnemy animation Texture Path Missing.\n");
                mind_free_all(EXIT_FAILURE);
            }
        }
        if (frames[i].img == NULL)
        {
            frames[i].img = mlx_texture_to_image(pd->mlx, frames[i].txtr);
            if (frames[i].img == NULL)
                mind_free_all(EXIT_FAILURE);
        }
    }
}

static void init_skin_walker_textures(t_parsed_data *pd)
{
    if (pd->shared_enemy_textures.skin_walker_initialized)
        return;
        
    load_shared_animation_frame(pd, pd->shared_enemy_textures.skin_walker_walk, 
        (char*[]){SKIN_WALKER_W1, SKIN_WALKER_W2, SKIN_WALKER_W3}, 3);
    load_shared_animation_frame(pd, pd->shared_enemy_textures.skin_walker_attack,
        (char*[]){SKIN_WALKER_A1, SKIN_WALKER_A2, SKIN_WALKER_A3}, 3);
    load_shared_animation_frame(pd, pd->shared_enemy_textures.skin_walker_death,
        (char*[]){SKIN_WALKER_D1, SKIN_WALKER_D2}, 2);
    
    pd->shared_enemy_textures.skin_walker_initialized = true;
}

static void init_memory_leak_textures(t_parsed_data *pd)
{
    if (pd->shared_enemy_textures.memory_leak_initialized)
        return;
        
    load_shared_animation_frame(pd, pd->shared_enemy_textures.memory_leak_walk,
        (char*[]){MEMORY_LEAK_W1, MEMORY_LEAK_W2, MEMORY_LEAK_W3}, 3);
    load_shared_animation_frame(pd, pd->shared_enemy_textures.memory_leak_attack,
        (char*[]){MEMORY_LEAK_A1, MEMORY_LEAK_A2, MEMORY_LEAK_A3}, 3);
    load_shared_animation_frame(pd, pd->shared_enemy_textures.memory_leak_death,
        (char*[]){MEMORY_LEAK_D1, MEMORY_LEAK_D2}, 2);
    
    pd->shared_enemy_textures.memory_leak_initialized = true;
}

static void init_segv_textures(t_parsed_data *pd)
{
    if (pd->shared_enemy_textures.segv_initialized)
        return;
        
    load_shared_animation_frame(pd, pd->shared_enemy_textures.segv_walk,
        (char*[]){SEGV_W1, SEGV_W2, SEGV_W3}, 3);
    load_shared_animation_frame(pd, pd->shared_enemy_textures.segv_attack,
        (char*[]){SEGV_A1, SEGV_A2, SEGV_A3}, 3);
    load_shared_animation_frame(pd, pd->shared_enemy_textures.segv_death,
        (char*[]){SEGV_D1, SEGV_D2}, 2);
    
    pd->shared_enemy_textures.segv_initialized = true;
}

static void init_default_skins(t_parsed_data *pd)
{
    // Load default skin textures
    if (pd->shared_enemy_textures.skin_walker_default.txtr == NULL)
    {
        pd->shared_enemy_textures.skin_walker_default.txtr = mlx_load_png(SKIN_WALKER_DFL);
        if (pd->shared_enemy_textures.skin_walker_default.txtr == NULL)
        {
            print_error("Error\nSkin Walker default texture missing.\n");
            mind_free_all(EXIT_FAILURE);
        }
    }
    
    if (pd->shared_enemy_textures.memory_leak_default.txtr == NULL)
    {
        pd->shared_enemy_textures.memory_leak_default.txtr = mlx_load_png(MEMORY_LEAK_DFL);
        if (pd->shared_enemy_textures.memory_leak_default.txtr == NULL)
        {
            print_error("Error\nMemory Leak default texture missing.\n");
            mind_free_all(EXIT_FAILURE);
        }
    }
    
    if (pd->shared_enemy_textures.segv_default.txtr == NULL)
    {
        pd->shared_enemy_textures.segv_default.txtr = mlx_load_png(SEGV_DFL);
        if (pd->shared_enemy_textures.segv_default.txtr == NULL)
        {
            print_error("Error\nSEGV default texture missing.\n");
            mind_free_all(EXIT_FAILURE);
        }
    }

     // Create default skin images (protect if these failed)
    if (pd->shared_enemy_textures.skin_walker_default.txtr && 
        !pd->shared_enemy_textures.skin_walker_default.img)
        pd->shared_enemy_textures.skin_walker_default.img = mlx_texture_to_image(pd->mlx, pd->shared_enemy_textures.skin_walker_default.txtr);
    
    if (pd->shared_enemy_textures.memory_leak_default.txtr && 
        !pd->shared_enemy_textures.memory_leak_default.img)
        pd->shared_enemy_textures.memory_leak_default.img = mlx_texture_to_image(pd->mlx,  pd->shared_enemy_textures.memory_leak_default.txtr);
    
    if (pd->shared_enemy_textures.segv_default.txtr && 
        !pd->shared_enemy_textures.segv_default.img)
        pd->shared_enemy_textures.segv_default.img = mlx_texture_to_image(pd->mlx,  pd->shared_enemy_textures.segv_default.txtr);

}


static void init_shared_textures(t_parsed_data *pd)
{
    if (pd->shared_enemy_textures.initialized)
        return;
    
    // Initialize the shared textures structure
    pd->shared_enemy_textures = (t_shared_enemy_textures){0};
    init_default_skins(pd);  // Load default skins first
    init_skin_walker_textures(pd);
    init_memory_leak_textures(pd);
    init_segv_textures(pd);
    
    pd->shared_enemy_textures.initialized = true;
}

static void	init_enemy_skin(t_parsed_data *pd, int i)
{
    if (pd->enemies[i].type == FT_SKIN_WALKER)
    {
        pd->enemies[i].skin = pd->shared_enemy_textures.skin_walker_default;
    }
    else if (pd->enemies[i].type == MEMORY_LEAK)
    {
        pd->enemies[i].skin = pd->shared_enemy_textures.memory_leak_default;
    }
    else if (pd->enemies[i].type == SEGV)
    {
        pd->enemies[i].skin = pd->shared_enemy_textures.segv_default;
    }
}

static void assign_shared_textures(t_parsed_data *pd, int i)
{
    t_enemy *enemy = &pd->enemies[i];
    
    if (enemy->type == FT_SKIN_WALKER)
    {
        enemy->walk1 = &pd->shared_enemy_textures.skin_walker_walk[0];
        enemy->walk2 = &pd->shared_enemy_textures.skin_walker_walk[1];
        enemy->walk3 = &pd->shared_enemy_textures.skin_walker_walk[2];
        enemy->attack1 = &pd->shared_enemy_textures.skin_walker_attack[0];
        enemy->attack2 = &pd->shared_enemy_textures.skin_walker_attack[1];
        enemy->attack3 = &pd->shared_enemy_textures.skin_walker_attack[2];
        enemy->death1 = &pd->shared_enemy_textures.skin_walker_death[0];
        enemy->death2 = &pd->shared_enemy_textures.skin_walker_death[1];
    }
    else if (enemy->type == MEMORY_LEAK)
    {
        enemy->walk1 = &pd->shared_enemy_textures.memory_leak_walk[0];
        enemy->walk2 = &pd->shared_enemy_textures.memory_leak_walk[1];
        enemy->walk3 = &pd->shared_enemy_textures.memory_leak_walk[2];
        enemy->attack1 = &pd->shared_enemy_textures.memory_leak_attack[0];
        enemy->attack2 = &pd->shared_enemy_textures.memory_leak_attack[1];
        enemy->attack3 = &pd->shared_enemy_textures.memory_leak_attack[2];
        enemy->death1 = &pd->shared_enemy_textures.memory_leak_death[0];
        enemy->death2 = &pd->shared_enemy_textures.memory_leak_death[1];
    }
    else if (enemy->type == SEGV)
    {
        enemy->walk1 = &pd->shared_enemy_textures.segv_walk[0];
        enemy->walk2 = &pd->shared_enemy_textures.segv_walk[1];
        enemy->walk3 = &pd->shared_enemy_textures.segv_walk[2];
        enemy->attack1 = &pd->shared_enemy_textures.segv_attack[0];
        enemy->attack2 = &pd->shared_enemy_textures.segv_attack[1];
        enemy->attack3 = &pd->shared_enemy_textures.segv_attack[2];
        enemy->death1 = &pd->shared_enemy_textures.segv_death[0];
        enemy->death2 = &pd->shared_enemy_textures.segv_death[1];
    }
}

static void init_animation_state(t_enemy *enemy)
{
    enemy->anim_img = enemy->skin.img;
    enemy->anim_frame = 0;
    enemy->anim_counter = 0;
    enemy->is_attacking = false;
    enemy->attack_anim_counter = 0;
    enemy->is_dying = false;
    enemy->death_anim_frame = 0;
    enemy->death_anim_counter = 0;
    enemy->death_timer = 0;
    enemy->is_highlighted = false;
    enemy->highlight_timer = 0;
    enemy->patrol_target_timer = 0;
    enemy->patrol_change_interval = 300;
}
// freee all shared images in shared images struct in pd 
// but keep the textures for future use
static void free_shared_enemy_textures(t_parsed_data *pd)
{
    int i;

    if (!pd->shared_enemy_textures.initialized)
        return;
    // free skin textures as well, default skin
    if (pd->shared_enemy_textures.skin_walker_default.txtr)
    {
        mlx_delete_texture(pd->shared_enemy_textures.skin_walker_default.txtr);
        pd->shared_enemy_textures.skin_walker_default.txtr = NULL;
    }
    if (pd->shared_enemy_textures.memory_leak_default.txtr)
    {
        mlx_delete_texture(pd->shared_enemy_textures.memory_leak_default.txtr);
        pd->shared_enemy_textures.memory_leak_default.txtr = NULL;
    }
    if (pd->shared_enemy_textures.segv_default.txtr)
    {
        mlx_delete_texture(pd->shared_enemy_textures.segv_default.txtr);
        pd->shared_enemy_textures.segv_default.txtr = NULL;
    }
    i = 0;
    while (i < 3)
    {
        if (pd->shared_enemy_textures.skin_walker_walk[i].txtr)
        {
            mlx_delete_texture(pd->shared_enemy_textures.skin_walker_walk[i].txtr);
            pd->shared_enemy_textures.skin_walker_walk[i].txtr = NULL;
        }
        if (pd->shared_enemy_textures.skin_walker_attack[i].txtr)
        {
            mlx_delete_texture(pd->shared_enemy_textures.skin_walker_attack[i].txtr);
            pd->shared_enemy_textures.skin_walker_attack[i].txtr = NULL;
        }
        if (pd->shared_enemy_textures.memory_leak_walk[i].txtr)
        {
            mlx_delete_texture(pd->shared_enemy_textures.memory_leak_walk[i].txtr);
            pd->shared_enemy_textures.memory_leak_walk[i].txtr = NULL;
        }
        if (pd->shared_enemy_textures.memory_leak_attack[i].txtr)
        {
            mlx_delete_texture(pd->shared_enemy_textures.memory_leak_attack[i].txtr);
            pd->shared_enemy_textures.memory_leak_attack[i].txtr = NULL;
        }
        if (pd->shared_enemy_textures.segv_walk[i].txtr)
        {
            mlx_delete_texture(pd->shared_enemy_textures.segv_walk[i].txtr);
            pd->shared_enemy_textures.segv_walk[i].txtr = NULL;
        }
        if (pd->shared_enemy_textures.segv_attack[i].txtr)
        {
            mlx_delete_texture(pd->shared_enemy_textures.segv_attack[i].txtr);
            pd->shared_enemy_textures.segv_attack[i].txtr = NULL;
        }
        i++;
    }

    i = 0;
    while (i < 2)
    {
        if (pd->shared_enemy_textures.skin_walker_death[i].txtr)
        {
            mlx_delete_texture(pd->shared_enemy_textures.skin_walker_death[i].txtr);
            pd->shared_enemy_textures.skin_walker_death[i].txtr = NULL;
        }
        if (pd->shared_enemy_textures.memory_leak_death[i].txtr)
        {
            mlx_delete_texture(pd->shared_enemy_textures.memory_leak_death[i].txtr);
            pd->shared_enemy_textures.memory_leak_death[i].txtr = NULL;
        }
        if (pd->shared_enemy_textures.segv_death[i].txtr)
        {
            mlx_delete_texture(pd->shared_enemy_textures.segv_death[i].txtr);
            pd->shared_enemy_textures.segv_death[i].txtr = NULL;
        }
        i++;
    }
}
    

void init_shared_enemy_textures(t_parsed_data *pd)
{
    int i;

    if (pd->enemy_count == 0 || pd->enemies == NULL)
        return;
    
    // Initialize shared textures once
    init_shared_textures(pd);
    
    i = 0;
    while (i < pd->enemy_count)
    {
        init_enemy_skin(pd, i);
        assign_shared_textures(pd, i);
        init_animation_state(&pd->enemies[i]);
        i++;
    }
    // to save on memory, only imgs are needed during gameplay, so free textures
    free_shared_enemy_textures(pd);
}

// // Function to free shared textures (call this on game shutdown)
// void free_shared_enemy_textures(t_parsed_data *pd)
// {
//     if (!pd->shared_enemy_textures.initialized)
//         return;
    
//     // Free skin walker textures
//     if (pd->shared_enemy_textures.skin_walker_initialized)
//     {
//         for (int i = 0; i < 3; i++)
//         {
//             if (pd->shared_enemy_textures.skin_walker_walk[i].img)
//                 mlx_delete_image(pd->mlx, pd->shared_enemy_textures.skin_walker_walk[i].img);
//             if (pd->shared_enemy_textures.skin_walker_walk[i].txtr)
//                 mlx_delete_texture(pd->shared_enemy_textures.skin_walker_walk[i].txtr);
            
//             if (pd->shared_enemy_textures.skin_walker_attack[i].img)
//                 mlx_delete_image(pd->mlx, pd->shared_enemy_textures.skin_walker_attack[i].img);
//             if (pd->shared_enemy_textures.skin_walker_attack[i].txtr)
//                 mlx_delete_texture(pd->shared_enemy_textures.skin_walker_attack[i].txtr);
//         }
//         for (int i = 0; i < 2; i++)
//         {
//             if (pd->shared_enemy_textures.skin_walker_death[i].img)
//                 mlx_delete_image(pd->mlx, pd->shared_enemy_textures.skin_walker_death[i].img);
//             if (pd->shared_enemy_textures.skin_walker_death[i].txtr)
//                 mlx_delete_texture(pd->shared_enemy_textures.skin_walker_death[i].txtr);
//         }
//     }
    
//     // Free memory leak textures
//     if (pd->shared_enemy_textures.memory_leak_initialized)
//     {
//         for (int i = 0; i < 3; i++)
//         {
//             if (pd->shared_enemy_textures.memory_leak_walk[i].img)
//                 mlx_delete_image(pd->mlx, pd->shared_enemy_textures.memory_leak_walk[i].img);
//             if (pd->shared_enemy_textures.memory_leak_walk[i].txtr)
//                 mlx_delete_texture(pd->shared_enemy_textures.memory_leak_walk[i].txtr);
            
//             if (pd->shared_enemy_textures.memory_leak_attack[i].img)
//                 mlx_delete_image(pd->mlx, pd->shared_enemy_textures.memory_leak_attack[i].img);
//             if (pd->shared_enemy_textures.memory_leak_attack[i].txtr)
//                 mlx_delete_texture(pd->shared_enemy_textures.memory_leak_attack[i].txtr);
//         }
//         for (int i = 0; i < 2; i++)
//         {
//             if (pd->shared_enemy_textures.memory_leak_death[i].img)
//                 mlx_delete_image(pd->mlx, pd->shared_enemy_textures.memory_leak_death[i].img);
//             if (pd->shared_enemy_textures.memory_leak_death[i].txtr)
//                 mlx_delete_texture(pd->shared_enemy_textures.memory_leak_death[i].txtr);
//         }
//     }
    
//     // Free SEGV textures
//     if (pd->shared_enemy_textures.segv_initialized)
//     {
//         for (int i = 0; i < 3; i++)
//         {
//             if (pd->shared_enemy_textures.segv_walk[i].img)
//                 mlx_delete_image(pd->mlx, pd->shared_enemy_textures.segv_walk[i].img);
//             if (pd->shared_enemy_textures.segv_walk[i].txtr)
//                 mlx_delete_texture(pd->shared_enemy_textures.segv_walk[i].txtr);
            
//             if (pd->shared_enemy_textures.segv_attack[i].img)
//                 mlx_delete_image(pd->mlx, pd->shared_enemy_textures.segv_attack[i].img);
//             if (pd->shared_enemy_textures.segv_attack[i].txtr)
//                 mlx_delete_texture(pd->shared_enemy_textures.segv_attack[i].txtr);
//         }
//         for (int i = 0; i < 2; i++)
//         {
//             if (pd->shared_enemy_textures.segv_death[i].img)
//                 mlx_delete_image(pd->mlx, pd->shared_enemy_textures.segv_death[i].img);
//             if (pd->shared_enemy_textures.segv_death[i].txtr)
//                 mlx_delete_texture(pd->shared_enemy_textures.segv_death[i].txtr);
//         }
//     }
    
//     // Reset the structure
//     pd->shared_enemy_textures = (t_shared_enemy_textures){0};
// }

