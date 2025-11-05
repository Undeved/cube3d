#include "../../cube.h"

void init_shared_attack_null(t_parsed_data *pd)
{
    int i;

    i = 0;
    while (i < 3)
	{
		pd->sh.skin_walker_walk[i].img = NULL;
		pd->sh.skin_walker_walk[i].txtr = NULL;
		pd->sh.skin_walker_attack[i].img = NULL;
		pd->sh.skin_walker_attack[i].txtr = NULL;
		pd->sh.memory_leak_walk[i].img = NULL;
		pd->sh.memory_leak_walk[i].txtr = NULL;
		pd->sh.memory_leak_attack[i].img = NULL;
		pd->sh.memory_leak_attack[i].txtr = NULL;
		pd->sh.segv_walk[i].img = NULL;
		pd->sh.segv_walk[i].txtr = NULL;
		pd->sh.segv_attack[i].img = NULL;
		pd->sh.segv_attack[i].txtr = NULL;
		i++;
	}
}

static void free_texture_set_null(mlx_texture_t **txtr)
{
    if (*txtr)
    {
        mlx_delete_texture(*txtr);
        *txtr = NULL;
    }
}

void free_sh_txtrs(t_parsed_data *pd)
{
    int i;

    free_texture_set_null(&pd->sh.skin_walker_default.txtr);
    free_texture_set_null(&pd->sh.memory_leak_default.txtr);
    free_texture_set_null(&pd->sh.segv_default.txtr);
    i = 0;
    while (i < 3)
    {
        free_texture_set_null(&pd->sh.skin_walker_walk[i].txtr);
        free_texture_set_null(&pd->sh.skin_walker_attack[i].txtr);
        free_texture_set_null(&pd->sh.memory_leak_walk[i].txtr);
        free_texture_set_null(&pd->sh.memory_leak_attack[i].txtr);
        free_texture_set_null(&pd->sh.segv_walk[i].txtr);
        free_texture_set_null(&pd->sh.segv_attack[i].txtr);
        i++;
    }
    i = 0;
    while (i < 2)
    {
        free_texture_set_null(&pd->sh.skin_walker_death[i].txtr);
        free_texture_set_null(&pd->sh.memory_leak_death[i].txtr);
        free_texture_set_null(&pd->sh.segv_death[i].txtr);
        i++;
    }
}
