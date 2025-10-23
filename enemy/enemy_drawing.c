#include "../cube.h"

void calculate_draw_bounds(t_enemy_draw_data *curr, int horizon,
        t_draw_bounds *b)
{
    b->orig_draw_start_y = -curr->sprite_height / 2 + horizon;
    b->orig_draw_start_x = -curr->sprite_width  / 2 + curr->sprite_screen_x;
    b->draw_start_y = b->orig_draw_start_y;
    if (b->draw_start_y < 0)
        b->draw_start_y = 0;
    b->draw_end_y = curr->sprite_height / 2 + horizon;
    if (b->draw_end_y >= HEIGHT)
        b->draw_end_y = HEIGHT - 1;
    b->draw_start_x = b->orig_draw_start_x;
    if (b->draw_start_x < 0)
        b->draw_start_x = 0;
    b->draw_end_x = curr->sprite_width / 2 + curr->sprite_screen_x;
    if (b->draw_end_x >= WIDTH)
        b->draw_end_x = WIDTH - 1;
}

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

void draw_enemy_pixel(t_draw_context *ctx, int stripe, int y)
{
    int             tex[2];
    t_tex_sample    sample;
    bool            depth_ok;

    if (ctx->curr->enemy->anim_img == NULL)
        return;
    if (ctx->curr->sprite_width == 0 || ctx->curr->sprite_height == 0)
        return;
    if (stripe < 0 || stripe >= ctx->pd->screen->width)
        return;

    tex[0] = (int)((stripe - ctx->b->orig_draw_start_x)
             * (double)ctx->curr->enemy->anim_img->width
             / (double)ctx->curr->sprite_width);
    tex[1] = (int)((y - ctx->b->orig_draw_start_y)
             * (double)ctx->curr->enemy->anim_img->height
             / (double)ctx->curr->sprite_height);
    sample = sample_texture_pixel(ctx->curr->enemy->anim_img, tex[0], tex[1]);
    if (!sample.ok)
        return;
    if (sample.alpha == 0)
        return;
    if (ctx->pd->zbuffer)
        depth_ok = (ctx->curr->transform.y < ctx->pd->zbuffer[stripe]);
    else
        depth_ok = true;

    if (!depth_ok)
        return;

    if (ctx->curr->enemy->is_highlighted)
    {
        mlx_put_pixel(ctx->pd->screen, stripe, y, 0xFFFFFFFF);
        return;
    }
    mlx_put_pixel(ctx->pd->screen, stripe, y,
        shade_color(sample.color, ctx->curr->distance, 0.15));
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
