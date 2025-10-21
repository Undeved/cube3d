#include "../cube.h"

void	init_texture_column(t_texture_column *tc)
{
	tc->tx = get_wall_texture(tc->pd, tc->side, tc->ray_dir);
	if (!tc->tx || !tc->tx->pixels)
	{
		draw_wall(tc->pd, tc->x, tc->line, 0x00FFFFFF);
		return ;
	}
	tc->tex_w = (int)tc->tx->width;
	tc->tex_h = (int)tc->tx->height;
	tc->screen_h = tc->pd->screen->height;
	if (tc->side == 0)
		tc->wall_x = tc->pos.y + tc->perp_dist * tc->ray_dir.y;
	else
		tc->wall_x = tc->pos.x + tc->perp_dist * tc->ray_dir.x;
	tc->wall_x -= floor(tc->wall_x);
	tc->tex_x = (int)(tc->wall_x * (double)tc->tex_w);
	if (tc->tex_x < 0)
		tc->tex_x = 0;
	if (tc->tex_x >= tc->tex_w)
		tc->tex_x = tc->tex_w - 1;
	tc->tex_x = tc->tex_w - tc->tex_x - 1;
	if (tc->side == 0 && tc->ray_dir.x > 0.0)
		tc->tex_x = tc->tex_w - tc->tex_x - 1;
	if (tc->side == 1 && tc->ray_dir.y < 0.0)
		tc->tex_x = tc->tex_w - tc->tex_x - 1;
}

void	setup_texture_stepping(t_texture_column *tc)
{
	tc->step = (double)tc->tex_h / (double)tc->line->height;
	tc->tex_pos = ((double)tc->line->draw_start
			- ((double)tc->screen_h / 2.0 + (double)tc->pd->player.pitch)
			+ (double)tc->line->height / 2.0) * tc->step;
}

uint32_t	get_pixel_color(t_texture_column *tc, int tex_y)
{
	unsigned char	*p;
	int				idx;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	p = (unsigned char *)tc->tx->pixels;
	idx = (tex_y * tc->tx->width + tc->tex_x) * 4;
	r = p[idx + 0];
	g = p[idx + 1];
	b = p[idx + 2];
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

void	draw_texture_pixels(t_texture_column *tc)
{
	int			y;
	int			tex_y;
	uint32_t	sample;

	y = tc->line->draw_start;
	while (y <= tc->line->draw_end)
	{
		tex_y = (int)tc->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tc->tex_h)
			tex_y = tc->tex_h - 1;
		sample = get_pixel_color(tc, tex_y);
		if (tc->side == 1)
			sample = darken_color(sample);
		mlx_put_pixel(tc->pd->screen, tc->x, y,
			shade_color(sample, tc->perp_dist, WALLS_FALLOF));
		tc->tex_pos += tc->step;
		y++;
	}
}

void draw_textured_column(t_parsed_data *pd, t_column_data *col, t_line_data *line)
{
	t_texture_column	tc;

	tc.pd = pd;
	tc.x = col->x;
	tc.line = line;
	tc.perp_dist = col->perp_dist;
	tc.side = col->side;
	tc.ray_dir = col->ray_dir;
	tc.pos = col->player_pos;

	init_texture_column(&tc);
	if (!tc.tx)
		return ;
	setup_texture_stepping(&tc);
	draw_texture_pixels(&tc);
}
