#include "../cube.h"

static void init_mini_map(t_parsed_data *pd)
{
    pd->minimap.img = mlx_new_image(pd->mlx, MINI_MAP_SIZE, MINI_MAP_SIZE);
    if (!pd->minimap.img || mlx_image_to_window(pd->mlx, pd->minimap.img, MINI_MAP_X, MINI_MAP_Y) == -1)
        mind_free_all(EXIT_FAILURE);
    pd->minimap.img->enabled = false;
    init_radar(pd);
}

static void init_gameplay_screen(t_parsed_data *pd)
{
    pd->screen = mlx_new_image(pd->mlx, WIDTH, HEIGHT);
    if(!pd->screen || mlx_image_to_window(pd->mlx, pd->screen, 0, 0) == -1)
        mind_free_all(EXIT_FAILURE);
    pd->screen->enabled = false;
    pd->zbuffer = allocate_gc(malloc(sizeof(double) * pd->screen->width));
    if (!pd->zbuffer)
        mind_free_all(EXIT_FAILURE);
}
static void load_one_texture(t_parsed_data *pd, t_texture *t)
{
	if (t->path == NULL)
		mind_free_all(EXIT_FAILURE);
	t->txtr = mlx_load_png(t->path);
	if (t->txtr == NULL)
    {
        print_error("Error\nTexture Path Missing.\n");
		mind_free_all(EXIT_FAILURE);
    }
	t->img = mlx_texture_to_image(pd->mlx, t->txtr);
	if (t->img == NULL)
		mind_free_all(EXIT_FAILURE);
	t->already_extracted = true;
}

void init_textures(t_parsed_data *pd)
{
	load_one_texture(pd, &pd->txtr_no);
	load_one_texture(pd, &pd->txtr_so);
	load_one_texture(pd, &pd->txtr_we);
	load_one_texture(pd, &pd->txtr_ea);
    init_shared_enemy_textures(pd);
    // init_enemy_textures(pd);
}

void game_loop(t_parsed_data *pd)
{
    init_precise_data(pd);
    init_all_textures(pd);
    set_pd(pd);
    pd->mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
    if(!pd->mlx)
        mind_free_all(EXIT_FAILURE);
    init_medkits(pd);
    init_door_texture(pd);
    init_textures(pd);
    init_gameplay_screen(pd);
    init_mini_map(pd);
    init_main_menu(pd);
    init_characters_menu(pd);
    mlx_key_hook(pd->mlx, handle_player_input, pd);
    mlx_cursor_hook(pd->mlx, handle_mouse_input, pd);
    mlx_mouse_hook(pd->mlx, handle_mouse_click, pd);
    mlx_loop_hook(pd->mlx, game_render, pd);
    mlx_loop(pd->mlx);
}
