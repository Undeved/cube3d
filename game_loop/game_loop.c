#include "../cube.h"

static void precise_direction(t_parsed_data *pd)
{
    if (pd->player.dir == 'N')
    {
        pd->player.bdir.x = 0;
        pd->player.bdir.y = -1;
    }
    else if (pd->player.dir == 'E')
    {
        pd->player.bdir.x = 1;
        pd->player.bdir.y = 0;
    }
    else if (pd->player.dir == 'S')
    {
        pd->player.bdir.x = 0;
        pd->player.bdir.y = 1;
    }
    else if (pd->player.dir == 'W')
    {
        pd->player.bdir.x = -1;
        pd->player.bdir.y = 0;
    }
}

static void init_key_flags(t_parsed_data *pd)
{
    int i;

    i = 0;
    while (i < KEYS_NUMBER)
        pd->keys.pressed[i++] = false;
}

static void init_precise_data(t_parsed_data *pd)
{
    pd->player.bpos.x = pd->player.pos.x + NUDGE_FROM_WALL;
    pd->player.bpos.y = pd->player.pos.y + NUDGE_FROM_WALL;
    pd->player.camera_plane.pos.x = pd->player.bdir.x * SCALER; // init camera plane
    pd->player.camera_plane.pos.y = pd->player.bdir.y * SCALER;
    pd->player.camera_plane.dir.x = pd->player.bdir.y;
    pd->player.camera_plane.dir.y = -pd->player.bdir.x;

    pd->level.game_started = false;
    pd->mouse_clicked = false;
    precise_direction(pd);
    init_key_flags(pd);
}

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

/* Role: initialize all wall textures (NO, SO, WE, EA).
 * Keep this call after mlx_init(pd->mlx) so PD->mlx is valid.
 */
void init_textures(t_parsed_data *pd)
{
	load_one_texture(pd, &pd->txtr_no);
	load_one_texture(pd, &pd->txtr_so);
	load_one_texture(pd, &pd->txtr_we);
	load_one_texture(pd, &pd->txtr_ea);
}

/* Role: free textures and images on shutdown.
 * Call from your cleanup path (mind_free_all / gc).
 */
void free_textures(t_parsed_data *pd)
{
	if (pd->txtr_no.img)
		mlx_delete_image(pd->mlx, pd->txtr_no.img);
	if (pd->txtr_no.txtr)
		mlx_delete_texture(pd->txtr_no.txtr);

	if (pd->txtr_so.img)
		mlx_delete_image(pd->mlx, pd->txtr_so.img);
	if (pd->txtr_so.txtr)
		mlx_delete_texture(pd->txtr_so.txtr);

	if (pd->txtr_we.img)
		mlx_delete_image(pd->mlx, pd->txtr_we.img);
	if (pd->txtr_we.txtr)
		mlx_delete_texture(pd->txtr_we.txtr);

	if (pd->txtr_ea.img)
		mlx_delete_image(pd->mlx, pd->txtr_ea.img);
	if (pd->txtr_ea.txtr)
		mlx_delete_texture(pd->txtr_ea.txtr);
}

void game_loop(t_parsed_data *pd)
{
    init_precise_data(pd);
    pd->mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
    if(!pd->mlx)
        mind_free_all(EXIT_FAILURE);
    init_textures(pd);
    init_gameplay_screen(pd);
    init_mini_map(pd);
    init_main_menu(pd);
    init_characters_menu(pd);
    init_game_ui(pd);
    mlx_key_hook(pd->mlx, handle_player_input, pd);
    mlx_cursor_hook(pd->mlx, handle_mouse_input, pd);
    mlx_mouse_hook(pd->mlx, handle_mouse_click, pd);
    mlx_loop_hook(pd->mlx, game_render, pd);
    mlx_loop(pd->mlx);
    mlx_terminate(pd->mlx); // remove this and keep it in gc
}
