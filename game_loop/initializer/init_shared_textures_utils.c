#include "../../cube.h"

static void load_shared_animation_frame(t_parsed_data *pd, t_raw_img *frames, char **paths, int count)
{
    int i;

    i = 0;
    while (i < count)
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
        i++;
    }
}

static void init_skin_walker_textures(t_parsed_data *pd)
{
    if (pd->sh.skin_walker_initialized)
        return;
        
    load_shared_animation_frame(pd, pd->sh.skin_walker_walk, 
        (char*[]){SKIN_WALKER_W1, SKIN_WALKER_W2, SKIN_WALKER_W3}, 3);
    load_shared_animation_frame(pd, pd->sh.skin_walker_attack,
        (char*[]){SKIN_WALKER_A1, SKIN_WALKER_A2, SKIN_WALKER_A3}, 3);
    load_shared_animation_frame(pd, pd->sh.skin_walker_death,
        (char*[]){SKIN_WALKER_D1, SKIN_WALKER_D2}, 2);
    
    pd->sh.skin_walker_initialized = true;
}

static void init_memory_leak_textures(t_parsed_data *pd)
{
    if (pd->sh.memory_leak_initialized)
        return;
        
    load_shared_animation_frame(pd, pd->sh.memory_leak_walk,
        (char*[]){MEMORY_LEAK_W1, MEMORY_LEAK_W2, MEMORY_LEAK_W3}, 3);
    load_shared_animation_frame(pd, pd->sh.memory_leak_attack,
        (char*[]){MEMORY_LEAK_A1, MEMORY_LEAK_A2, MEMORY_LEAK_A3}, 3);
    load_shared_animation_frame(pd, pd->sh.memory_leak_death,
        (char*[]){MEMORY_LEAK_D1, MEMORY_LEAK_D2}, 2);
    
    pd->sh.memory_leak_initialized = true;
}

static void init_segv_textures(t_parsed_data *pd)
{
    if (pd->sh.segv_initialized)
        return;
        
    load_shared_animation_frame(pd, pd->sh.segv_walk,
        (char*[]){SEGV_W1, SEGV_W2, SEGV_W3}, 3);
    load_shared_animation_frame(pd, pd->sh.segv_attack,
        (char*[]){SEGV_A1, SEGV_A2, SEGV_A3}, 3);
    load_shared_animation_frame(pd, pd->sh.segv_death,
        (char*[]){SEGV_D1, SEGV_D2}, 2);
    
    pd->sh.segv_initialized = true;
}

void init_shared_textures(t_parsed_data *pd)
{
    if (pd->sh.initialized)
        return;
    // Initialize the shared textures structure
    pd->sh = (t_sh){0};
    init_default_skins(pd);  // Load default skins first
    init_skin_walker_textures(pd);
    init_memory_leak_textures(pd);
    init_segv_textures(pd);
    
    pd->sh.initialized = true;
}
