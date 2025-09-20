#include "cube.h"
#include <math.h>

/* Hardcoded map (1 = wall, 0 = empty) */
static char *map[] = {
    "1111111111",
    "1000101001",
    "1000001001",
    "1000001001",
    "1000000001",
    "1111111111",
    NULL
};

#define MAP_W 10
#define MAP_H 6
#define FOV (M_PI / 3)       // 60 degrees
#define NUM_RAYS WIDTH       // one ray per screen column
#define MOVE_SPEED 0.1
#define ROT_SPEED  0.08
#define WALL_COLOR 0xFF0000FF  // red walls (RGBA)

/* Player state (now static so it persists between frames) */
static double px = 3.0;
static double py = 3.0;
static double pa = 0.0;

/* Check if a position hits a wall */
static int is_wall(double x, double y)
{
    int mx = (int)x;
    int my = (int)y;
    if (mx < 0 || mx >= MAP_W || my < 0 || my >= MAP_H)
        return (1);
    return (map[my][mx] == '1');
}

/*
 * Simple function to handle input and cast rays
 */
void simple_raycast(void *param)
{
    mlx_t *mlx = param;
    static mlx_image_t *img = NULL;

    /* create image only once */
    if (!img)
    {
        img = mlx_new_image(mlx, WIDTH, HEIGHT);
        if (!img)
            return;
        mlx_image_to_window(mlx, img, 0, 0);
    }

    /* handle input */
    if (mlx_is_key_down(mlx, MLX_KEY_W))
    {
        double nx = px + cos(pa) * MOVE_SPEED;
        double ny = py + sin(pa) * MOVE_SPEED;
        if (!is_wall(nx, py)) px = nx;
        if (!is_wall(px, ny)) py = ny;
    }
    if (mlx_is_key_down(mlx, MLX_KEY_S))
    {
        double nx = px - cos(pa) * MOVE_SPEED;
        double ny = py - sin(pa) * MOVE_SPEED;
        if (!is_wall(nx, py)) px = nx;
        if (!is_wall(px, ny)) py = ny;
    }
    if (mlx_is_key_down(mlx, MLX_KEY_A))
        pa -= ROT_SPEED;
    if (mlx_is_key_down(mlx, MLX_KEY_D))
        pa += ROT_SPEED;

    /* clear image */
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        ((uint32_t *)img->pixels)[i] = 0x000000FF; // black background

    /* cast rays */
    for (int x = 0; x < NUM_RAYS; x++)
    {
        double ray_angle = pa - (FOV / 2) + ((double)x / NUM_RAYS) * FOV;
        double ray_dx = cos(ray_angle);
        double ray_dy = sin(ray_angle);

        double dist = 0.0;
        int hit = 0;
        while (!hit && dist < 20.0)
        {
            dist += 0.05;
            int test_x = (int)(px + ray_dx * dist);
            int test_y = (int)(py + ray_dy * dist);
            if (test_x < 0 || test_x >= MAP_W || test_y < 0 || test_y >= MAP_H)
                hit = 1;
            else if (map[test_y][test_x] == '1')
                hit = 1;
        }

        /* correct fisheye effect */
        double corrected = dist * cos(ray_angle - pa);

        double wall_h = HEIGHT / (corrected + 0.0001);
        int start = (HEIGHT / 2) - (wall_h / 2);
        int end   = (HEIGHT / 2) + (wall_h / 2);
        if (start < 0) start = 0;
        if (end >= HEIGHT) end = HEIGHT - 1;

        for (int y = start; y < end; y++)
            mlx_put_pixel(img, x, y, WALL_COLOR);
    }
}
