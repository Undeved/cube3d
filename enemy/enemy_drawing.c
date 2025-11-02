#include "../cube.h"

t_tex_sample sample_texture_pixel(mlx_image_t *img, int tx, int ty)
{
    t_tex_sample    s;
    unsigned char   *p;
    int             idx;
    int             size[2];

    s.ok = 0;
    s.color = 0;
    s.alpha = 0;
    if (!img)
        return (s);
    size[0] = img->width;
    size[1] = img->height;
    if (tx < 0 || tx >= size[0] || ty < 0 || ty >= size[1])
        return (s);
    p = (unsigned char *)img->pixels;
    idx = (ty * size[0] + tx) * 4;
    s.alpha = p[idx + 3];
    s.color = (p[idx + 0] << 24) | (p[idx + 1] << 16)
        | (p[idx + 2] << 8) | p[idx + 3];
    s.ok = 1;
    return (s);
}

static bool	get_enemy_sample(t_draw_context *ctx, int stripe,
				int y, t_tex_sample *sample)
{
	int		tex[2];

	if (ctx->curr->enemy->anim_img == NULL)
		return (false);
	if (ctx->curr->sprite_width == 0 || ctx->curr->sprite_height == 0)
		return (false);
	if (stripe < 0 || stripe >= ctx->pd->screen->width)
		return (false);
	tex[0] = (int)((stripe - ctx->b->orig_draw_start_x)
			* (double)ctx->curr->enemy->anim_img->width
			/ (double)ctx->curr->sprite_width);
	tex[1] = (int)((y - ctx->b->orig_draw_start_y)
			* (double)ctx->curr->enemy->anim_img->height
			/ (double)ctx->curr->sprite_height);
	*sample = sample_texture_pixel(ctx->curr->enemy->anim_img,
			tex[0], tex[1]);
	if (!sample->ok || sample->alpha == 0)
		return (false);
	return (true);
}

void	draw_enemy_pixel(t_draw_context *ctx, int stripe, int y)
{
	t_tex_sample	sample;
	bool			depth_ok;
	uint32_t		color;

	if (!get_enemy_sample(ctx, stripe, y, &sample))
		return;
	if (ctx->pd->zbuffer)
		depth_ok = (ctx->curr->transform.y < ctx->pd->zbuffer[stripe]);
	else
		depth_ok = true;
	if (!depth_ok)
		return;
	color = shade_color(sample.color, ctx->curr->distance, 0.15);
	if (ctx->curr->enemy->is_highlighted)
		color = tint_with_white(color, 0.50f);
	mlx_put_pixel(ctx->pd->screen, stripe, y, color);
}

void draw_enemy_sprite(t_draw_context *ctx)
{
    int stripe;
    int y;

    stripe = ctx->b->draw_start_x;
    while (stripe < ctx->b->draw_end_x)
    {
        if (stripe >= 0 && stripe < ctx->pd->screen->width)
        {
            y = ctx->b->draw_start_y;
            while (y < ctx->b->draw_end_y)
            {
                draw_enemy_pixel(ctx, stripe, y);
                y++;
            }
        }
        stripe++;
    }
}

void draw_single_enemy(t_parsed_data *pd, t_enemy_draw_data *curr,
        int horizon)
{
    t_draw_bounds    b;
    t_draw_context   ctx;

    calculate_draw_bounds(curr, horizon, &b);
    ctx.pd = pd;
    ctx.curr = curr;
    ctx.b = &b;
    draw_enemy_sprite(&ctx);
}
