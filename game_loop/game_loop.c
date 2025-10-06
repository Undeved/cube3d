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
    pd->player.pitch = 0;
    pd->player.health = PLAYER_HEALTH;
    pd->game_ui.health.img = NULL;
    pd->player.gun.ammo = AMMO;
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

static void free_enemy_textures(t_parsed_data *pd)
{
    int i;

    if (pd->enemy_count == 0 || pd->enemies == NULL)
        return ;
    i = 0;
    while (i < pd->enemy_count)
    {
        if (pd->enemies[i].skin.txtr)
        {
            mlx_delete_texture(pd->enemies[i].skin.txtr);
            pd->enemies[i].skin.txtr = NULL;
        }
        
        // Free walk textures
        if (pd->enemies[i].walk1.txtr)
        {
            mlx_delete_texture(pd->enemies[i].walk1.txtr);
            pd->enemies[i].walk1.txtr = NULL;
        }
        if (pd->enemies[i].walk2.txtr)
        {
            mlx_delete_texture(pd->enemies[i].walk2.txtr);
            pd->enemies[i].walk2.txtr = NULL;
        }
        if (pd->enemies[i].walk3.txtr)
        {
            mlx_delete_texture(pd->enemies[i].walk3.txtr);
            pd->enemies[i].walk3.txtr = NULL;
        }
        
        // Free attack textures
        if (pd->enemies[i].attack1.txtr)
        {
            mlx_delete_texture(pd->enemies[i].attack1.txtr);
            pd->enemies[i].attack1.txtr = NULL;
        }
        if (pd->enemies[i].attack2.txtr)
        {
            mlx_delete_texture(pd->enemies[i].attack2.txtr);
            pd->enemies[i].attack2.txtr = NULL;
        }
        if (pd->enemies[i].attack3.txtr)
        {
            mlx_delete_texture(pd->enemies[i].attack3.txtr);
            pd->enemies[i].attack3.txtr = NULL;
        }
        i++;
    }
}

void init_enemy_textures(t_parsed_data *pd)
{
    int i;
    const char *walk1_path;
    const char *walk2_path;
    const char *walk3_path;
    const char *attack1_path;
    const char *attack2_path;
    const char *attack3_path;

    if (pd->enemy_count == 0 || pd->enemies == NULL)
        return ;
    i = 0;
    while (i < pd->enemy_count)
    {
        if (pd->enemies[i].skin.txtr == NULL)
        {
            if (pd->enemies[i].type == FT_SKIN_WALKER)
            {
                pd->enemies[i].skin.txtr = mlx_load_png(SKIN_WALKER);
                if (pd->enemies[i].skin.txtr == NULL)
                {
                    print_error("Error\nEnemy Texture Path Missing.\n");
                    mind_free_all(EXIT_FAILURE);
                }
            }
            else if (pd->enemies[i].type == MEMORY_LEAK)
            {
                pd->enemies[i].skin.txtr = mlx_load_png(SKIN_WALKER); // change later
                if (pd->enemies[i].skin.txtr == NULL)
                {
                    print_error("Error\nEnemy Texture Path Missing.\n");
                    mind_free_all(EXIT_FAILURE);
                }
            }
            else if (pd->enemies[i].type == SEGV)
            {
                pd->enemies[i].skin.txtr = mlx_load_png(SKIN_WALKER); // change later
                if (pd->enemies[i].skin.txtr == NULL)
                {
                    print_error("Error\nEnemy Texture Path Missing.\n");
                    mind_free_all(EXIT_FAILURE);
                }
            }
        }
        if (pd->enemies[i].skin.img == NULL)
        {
            pd->enemies[i].skin.img = mlx_texture_to_image(pd->mlx, pd->enemies[i].skin.txtr);
            if (pd->enemies[i].skin.img == NULL)
                mind_free_all(EXIT_FAILURE);
        }

        /* --- decide per-type walk frame paths --- */
        if (pd->enemies[i].type == FT_SKIN_WALKER)
        {
            walk1_path = SKIN_WALKER_W1;
            walk2_path = SKIN_WALKER_W2;
            walk3_path = SKIN_WALKER_W3;
            attack1_path = SKIN_WALKER_A1;
            attack2_path = SKIN_WALKER_A2;
            attack3_path = SKIN_WALKER_A3;
        }
        // else if (pd->enemies[i].type == MEMORY_LEAK)
        // {
        //     walk1_path = MEMORY_LEAK_W1;
        //     walk2_path = MEMORY_LEAK_W2;
        //     walk3_path = MEMORY_LEAK_W3;
        // }
        // else /* SEGV or fallback */
        // {
        //     walk1_path = SEGV_W1;
        //     walk2_path = SEGV_W2;
        //     walk3_path = SEGV_W3;
        // }

        /* --- load walk1 texture -> image --- */
        if (pd->enemies[i].walk1.txtr == NULL)
        {
            pd->enemies[i].walk1.txtr = mlx_load_png(walk1_path);
            if (pd->enemies[i].walk1.txtr == NULL)
            {
                print_error("Error\nEnemy walk1 Texture Path Missing.\n");
                mind_free_all(EXIT_FAILURE);
            }
        }
        if (pd->enemies[i].walk1.img == NULL)
        {
            pd->enemies[i].walk1.img = mlx_texture_to_image(pd->mlx, pd->enemies[i].walk1.txtr);
            if (pd->enemies[i].walk1.img == NULL)
                mind_free_all(EXIT_FAILURE);
        }

        /* --- load walk2 texture -> image --- */
        if (pd->enemies[i].walk2.txtr == NULL)
        {
            pd->enemies[i].walk2.txtr = mlx_load_png(walk2_path);
            if (pd->enemies[i].walk2.txtr == NULL)
            {
                print_error("Error\nEnemy walk2 Texture Path Missing.\n");
                mind_free_all(EXIT_FAILURE);
            }
        }
        if (pd->enemies[i].walk2.img == NULL)
        {
            pd->enemies[i].walk2.img = mlx_texture_to_image(pd->mlx, pd->enemies[i].walk2.txtr);
            if (pd->enemies[i].walk2.img == NULL)
                mind_free_all(EXIT_FAILURE);
        }

        /* --- load walk3 texture -> image --- */
        if (pd->enemies[i].walk3.txtr == NULL)
        {
            pd->enemies[i].walk3.txtr = mlx_load_png(walk3_path);
            if (pd->enemies[i].walk3.txtr == NULL)
            {
                print_error("Error\nEnemy walk3 Texture Path Missing.\n");
                mind_free_all(EXIT_FAILURE);
            }
        }
        if (pd->enemies[i].walk3.img == NULL)
        {
            pd->enemies[i].walk3.img = mlx_texture_to_image(pd->mlx, pd->enemies[i].walk3.txtr);
            if (pd->enemies[i].walk3.img == NULL)
                mind_free_all(EXIT_FAILURE);
        }
              if (pd->enemies[i].attack1.txtr == NULL)
        {
            pd->enemies[i].attack1.txtr = mlx_load_png(attack1_path);
            if (pd->enemies[i].attack1.txtr == NULL)
            {
                print_error("Error\nEnemy attack1 Texture Path Missing.\n");
                mind_free_all(EXIT_FAILURE);
            }
        }
        if (pd->enemies[i].attack1.img == NULL)
        {
            pd->enemies[i].attack1.img = mlx_texture_to_image(pd->mlx, pd->enemies[i].attack1.txtr);
            if (pd->enemies[i].attack1.img == NULL)
                mind_free_all(EXIT_FAILURE);
        }

        if (pd->enemies[i].attack2.txtr == NULL)
        {
            pd->enemies[i].attack2.txtr = mlx_load_png(attack2_path);
            if (pd->enemies[i].attack2.txtr == NULL)
            {
                print_error("Error\nEnemy attack2 Texture Path Missing.\n");
                mind_free_all(EXIT_FAILURE);
            }
        }
        if (pd->enemies[i].attack2.img == NULL)
        {
            pd->enemies[i].attack2.img = mlx_texture_to_image(pd->mlx, pd->enemies[i].attack2.txtr);
            if (pd->enemies[i].attack2.img == NULL)
                mind_free_all(EXIT_FAILURE);
        }

        if (pd->enemies[i].attack3.txtr == NULL)
        {
            pd->enemies[i].attack3.txtr = mlx_load_png(attack3_path);
            if (pd->enemies[i].attack3.txtr == NULL)
            {
                print_error("Error\nEnemy attack3 Texture Path Missing.\n");
                mind_free_all(EXIT_FAILURE);
            }
        }
        if (pd->enemies[i].attack3.img == NULL)
        {
            pd->enemies[i].attack3.img = mlx_texture_to_image(pd->mlx, pd->enemies[i].attack3.txtr);
            if (pd->enemies[i].attack3.img == NULL)
                mind_free_all(EXIT_FAILURE);
        }

        /* --- set default animation image and counters (immediately after loading frames) --- */
        pd->enemies[i].anim_img = pd->enemies[i].skin.img; /* start with base skin until walking */
        pd->enemies[i].anim_frame = 0;
        pd->enemies[i].anim_counter = 0;
        pd->enemies[i].is_attacking = false;
        pd->enemies[i].attack_anim_counter = 0;

        i++;
    }
    free_enemy_textures(pd); // free the textures after converting them to images
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
    init_enemy_textures(pd);
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

static void init_enemy_textures_to_null(t_parsed_data *pd)
{
    int i;

    if (pd->enemy_count == 0 || pd->enemies == NULL)
        return ;
    i = 0;
    while (i < pd->enemy_count)
    {
        pd->enemies[i].skin.txtr = NULL;
        pd->enemies[i].skin.img = NULL;

        pd->enemies[i].walk1.txtr = NULL;
        pd->enemies[i].walk1.img  = NULL;
        pd->enemies[i].walk2.txtr = NULL;
        pd->enemies[i].walk2.img  = NULL;
        pd->enemies[i].walk3.txtr = NULL;
        pd->enemies[i].walk3.img  = NULL;

        // Initialize attack textures to null
        pd->enemies[i].attack1.txtr = NULL;
        pd->enemies[i].attack1.img  = NULL;
        pd->enemies[i].attack2.txtr = NULL;
        pd->enemies[i].attack2.img  = NULL;
        pd->enemies[i].attack3.txtr = NULL;
        pd->enemies[i].attack3.img  = NULL;

        pd->enemies[i].anim_img = NULL;
        pd->enemies[i].anim_frame = 0;
        pd->enemies[i].anim_counter = 0;
        pd->enemies[i].is_attacking = false;
        pd->enemies[i].attack_anim_counter = 0;
        i++;
    }
}


void game_loop(t_parsed_data *pd)
{
    init_enemy_textures_to_null(pd);
    pd->mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
    if(!pd->mlx)
        mind_free_all(EXIT_FAILURE);
    init_precise_data(pd);
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
