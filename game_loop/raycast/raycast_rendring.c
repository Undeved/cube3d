#include "../../cube.h"

/*draw_wall used by textured fallback */
static void draw_wall(t_parsed_data *pd, int x, t_line_data *line, uint32_t wall_col)
{
	int y;

	y = line->draw_start;
	while (y <= line->draw_end)
	{
		mlx_put_pixel(pd->screen, x, y, wall_col);
		y++;
	}
}

/* Select the correct wall texture (NO / SO / WE / EA) */
static mlx_texture_t *get_wall_texture(t_parsed_data *pd, int side, t_bdir ray_dir)
{
	mlx_texture_t *tx;

	if (side == 0)
	{
		if (ray_dir.x > 0)
			tx = pd->txtr_we.txtr;
		else
			tx = pd->txtr_ea.txtr;
	}
	else
	{
		if (ray_dir.y > 0)
			tx = pd->txtr_no.txtr;
		else
			tx = pd->txtr_so.txtr;
	}
	return (tx);
}

/* darken a 32-bit packed color (same byte layout you use for sample) */
static inline uint32_t darken_color(uint32_t c)
{
	uint32_t r = (c >> 24) & 0xFF;
	uint32_t g = (c >> 16) & 0xFF;
	uint32_t b = (c >> 8) & 0xFF;
	r >>= 1; g >>= 1; b >>= 1;
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

/* draw textured vertical column */
static void draw_textured_column(t_parsed_data *pd, int x, t_line_data *line,
					 double perp_dist, int side, t_bdir ray_dir, t_bpos pos)
{
	mlx_texture_t *tx;
	double		 wall_x;
	int			 tex_x;
	int			 tex_y;
	int			 y;
	int			 tex_h;
	int			 tex_w;
	double		 step;
	double		 tex_pos;
	int			 screen_h;

	tx = get_wall_texture(pd, side, ray_dir);
	if (!tx || !tx->pixels)
	{
		draw_wall(pd, x, line, 0x00FFFFFF);
		return ;
	}

	tex_w = (int)tx->width;
	tex_h = (int)tx->height;
	screen_h = pd->screen->height;

	if (side == 0)
		wall_x = pos.y + perp_dist * ray_dir.y;
	else
		wall_x = pos.x + perp_dist * ray_dir.x;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * (double)tex_w);
	if (tex_x < 0) tex_x = 0;
	if (tex_x >= tex_w) tex_x = tex_w - 1;

	if (side == 0 && ray_dir.x > 0.0)
		tex_x = tex_w - tex_x - 1;
	if (side == 1 && ray_dir.y < 0.0)
		tex_x = tex_w - tex_x - 1;

	step = (double)tex_h / (double)line->height;
	tex_pos = ((double)line->draw_start
           - ((double)screen_h / 2.0 + (double)pd->player.pitch)
           + (double)line->height / 2.0) * step;

	y = line->draw_start;
	while (y <= line->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0) tex_y = 0;
		if (tex_y >= tex_h) tex_y = tex_h - 1;

		/* safe byte-based sampling (assumes 4 bytes per pixel: R,G,B,A) */
		{
			unsigned char *p = (unsigned char *)tx->pixels;
			int idx = (tex_y * tx->width + tex_x) * 4;
			unsigned int r = p[idx + 0];
			unsigned int g = p[idx + 1];
			unsigned int b = p[idx + 2];
			uint32_t sample = (r << 24) | (g << 16) | (b << 8) | 0xFF;

			if (side == 1)
				sample = darken_color(sample);

			mlx_put_pixel(pd->screen, x, y, shade_color(sample, perp_dist, WALLS_FALLOF));
		}

		tex_pos += step;
		y++;
	}
}

/* delta distances for DDA */
static void compute_delta_dist(t_bdir ray_dir, t_bpos *delta_dist)
{
	if (ray_dir.x == 0.0)
		delta_dist->x = 1000000.0;
	else
		delta_dist->x = fabs(1.0 / ray_dir.x);
	if (ray_dir.y == 0.0)
		delta_dist->y = 1000000.0;
	else
		delta_dist->y = fabs(1.0 / ray_dir.y);
}

/* init x step + initial sidedist */
static void set_x_step(t_bpos pos, t_pos map, t_bdir ray_dir, t_step_data *data)
{
	if (ray_dir.x < 0.0)
	{
		data->step->x = -1;
		data->side_dist->x = (pos.x - (double)map.x) * data->delta_dist.x;
	}
	else
	{
		data->step->x = 1;
		data->side_dist->x = ((double)map.x + 1.0 - pos.x) * data->delta_dist.x;
	}
}

/* init y step + initial sidedist */
static void set_y_step(t_bpos pos, t_pos map, t_bdir ray_dir, t_step_data *data)
{
	if (ray_dir.y < 0.0)
	{
		data->step->y = -1;
		data->side_dist->y = (pos.y - (double)map.y) * data->delta_dist.y;
	}
	else
	{
		data->step->y = 1;
		data->side_dist->y = ((double)map.y + 1.0 - pos.y) * data->delta_dist.y;
	}
}

static void init_step_and_sidedist(t_bpos player, t_step_data *data)
{
	set_x_step(player, data->map, data->ray_dir, data);
	set_y_step(player, data->map, data->ray_dir, data);
}

static void update_x_side(t_dda_data *data)
{
	data->side_dist->x += data->delta_dist.x;
	data->map->x += data->step.x;
	*data->side = 0;
}

static void update_y_side(t_dda_data *data)
{
	data->side_dist->y += data->delta_dist.y;
	data->map->y += data->step.y;
	*data->side = 1;
}

static bool is_wall_hit(t_parsed_data *pd, t_pos map)
{
	if (map.y < 0 || !pd->map_grid[map.y])
		return (false);
	if (map.x < 0 || !pd->map_grid[map.y][map.x])
		return (false);
	return (pd->map_grid[map.y][map.x] != '0');
}

static void perform_dda(t_parsed_data *pd, t_dda_data *data)
{
	while (1)
	{
		if (data->side_dist->x < data->side_dist->y)
			update_x_side(data);
		else
			update_y_side(data);
		if (is_wall_hit(pd, *data->map))
			break ;
	}
}

static double calc_x_perp_dist(t_pos map, t_bpos pos, t_pos step, t_bdir ray_dir)
{
	if (ray_dir.x == 0.0)
		return (0.000001);
	return (((double)map.x - pos.x + (1 - step.x) / 2.0) / ray_dir.x);
}

static double calc_y_perp_dist(t_pos map, t_bpos pos, t_pos step, t_bdir ray_dir)
{
	if (ray_dir.y == 0.0)
		return (0.000001);
	return (((double)map.y - pos.y + (1 - step.y) / 2.0) / ray_dir.y);
}

static double compute_perp_wall_dist(t_perp_data *data)
{
	double	perp_wall_dist;

	if (data->side == 0)
		perp_wall_dist = calc_x_perp_dist(data->map, data->pos, data->step, data->ray_dir);
	else
		perp_wall_dist = calc_y_perp_dist(data->map, data->pos, data->step, data->ray_dir);
	if (perp_wall_dist <= 0.0)
		perp_wall_dist = 0.000001;
	return (perp_wall_dist);
}

static void calc_line_params(int h, double perp_dist, t_line_data *line, t_parsed_data *pd)
{
	line->height = (int)((double)h / perp_dist);
	line->draw_start = -line->height / 2 + (h / 2 + (int)pd->player.pitch);
	if (line->draw_start < 0)
		line->draw_start = 0;
	line->draw_end = line->height / 2 + (h / 2 + (int)pd->player.pitch);
	if (line->draw_end >= h)
		line->draw_end = h - 1;
}

static void draw_ceiling(t_parsed_data *pd, int x, int draw_start, int horizon)
{
	int		 y;
	uint32_t color;

	y = 0;
	while (y < draw_start)
	{
		color = shade_color(CEILING, horizon + y, ROOF_FALLOF);
		mlx_put_pixel(pd->screen, x, y, color);
		y++;
	}
}

static void draw_floor(t_parsed_data *pd, int x, int draw_end, int horizon)
{
	int		 y;
	uint32_t color;

	y = draw_end + 1;
	while (y < (horizon * 2))
	{
		color = shade_color(FLOOR, ((horizon * 2) + SHIFT_FLOOR_SHADE) - y, FLOOR_FALLOF);
		mlx_put_pixel(pd->screen, x, y, color);
		y++;
	}
}

static void draw_column(t_parsed_data *pd, t_column_data *col)
{
	t_line_data line;

	calc_line_params(col->h, col->perp_dist, &line, pd);
	draw_ceiling(pd, col->x, line.draw_start, col->h / 2);
	draw_textured_column(pd, col->x, &line, col->perp_dist, col->side,
						 col->ray_dir, col->player_pos);
	draw_floor(pd, col->x, line.draw_end, col->h / 2);
}

static void set_ray_dir(t_ray_dir_data *data)
{
	double camera_x;

	camera_x = 2.0 * data->x / (double)data->w - 1.0;
	data->ray_dir->x = data->pl->bdir.x + -data->cam->dir.x * camera_x;
	data->ray_dir->y = data->pl->bdir.y + -data->cam->dir.y * camera_x;
}

static void init_ray_data(t_ray_data *ray, t_player *pl, int x, int w)
{
	t_ray_dir_data ray_dir_data;

	ray_dir_data.pl = pl;
	ray_dir_data.cam = &pl->camera_plane;
	ray_dir_data.x = x;
	ray_dir_data.w = w;
	ray_dir_data.ray_dir = &ray->ray_dir;
	set_ray_dir(&ray_dir_data);
	ray->player_pos.x = pl->bpos.x;
	ray->player_pos.y = pl->bpos.y;
	ray->map.x = (int)ray->player_pos.x;
	ray->map.y = (int)ray->player_pos.y;
}

static void init_dda_data(t_parsed_data *pd, t_ray_data *ray, t_dda_data *dda_data)
{
	dda_data->pd = pd;
	dda_data->map = &ray->map;
	dda_data->side_dist = &ray->side_dist;
	dda_data->delta_dist = ray->delta_dist;
	dda_data->step = ray->step;
	dda_data->side = &ray->side;
}

static void init_perp_and_col_data(t_parsed_data *pd, int x, t_ray_data *ray,
					   t_perp_data *perp_data, t_column_data *col_data)
{
	perp_data->map = ray->map;
	perp_data->pos = ray->player_pos;
	perp_data->step = ray->step;
	perp_data->ray_dir = ray->ray_dir;
	perp_data->side = ray->side;
	col_data->pd = pd;
	col_data->x = x;
	col_data->h = pd->screen->height;
	col_data->perp_dist = compute_perp_wall_dist(perp_data);
	col_data->side = ray->side;
	col_data->ray_dir = ray->ray_dir;
	col_data->player_pos = ray->player_pos;
}

static void cast_single_ray(t_parsed_data *pd, int x)
{
	t_ray_data	ray;
	t_step_data	step_data;
	t_dda_data	dda_data;
	t_perp_data	perp_data;
	t_column_data col_data;

	init_ray_data(&ray, &pd->player, x, pd->screen->width);
	compute_delta_dist(ray.ray_dir, &ray.delta_dist);
	step_data.ray_dir = ray.ray_dir;
	step_data.delta_dist = ray.delta_dist;
	step_data.map = ray.map;
	step_data.step = &ray.step;
	step_data.side_dist = &ray.side_dist;
	init_step_and_sidedist(ray.player_pos, &step_data);
	init_dda_data(pd, &ray, &dda_data);
	perform_dda(pd, &dda_data);
	init_perp_and_col_data(pd, x, &ray, &perp_data, &col_data);
	draw_column(pd, &col_data);
}

void raycast_render(t_parsed_data *pd)
{
	int	x;
	int	w;

	w = pd->screen->width;
	x = 0;
	while (x < w)
	{
		cast_single_ray(pd, x);
		x++;
	}
	draw_enemies(pd);
}
