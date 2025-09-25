#include "../../cube.h"

 // hna ghadir lcode dialk
 /*
    struct pd is parsed data_ have all important things

    ====== > pd.map_grid
    double char **full map
    [1, 1, 1, 1, 1, 1, 1, 1]
    [1, 0, 0, 0, 1, 0, 0, 1]
    [1, 0, 0, 0, 0, 0, 0, 1]
    [1, 0, 0, 0, N, 0, 0, 1]
    [1, 0, 0, 0, 0, 0, 0, 1]
    [1, 0, 0, 0, 0, 0, 0, 1]
    [1, 1, 1, 1, 1, 1, 1, 1]

    ====== > pd.player
    player struct
    position [x, z] bpos
    vector direction [x, z] bdir
 */

// raycast_split.c
#include <math.h>
#include <stdint.h>

/*
 * Compute delta distances for the ray: the distance the ray has to travel
 * to go from one x-side to the next (deltaDistX) and from one y-side to the next (deltaDistY).
 * Uses simple decimal constants instead of scientific notation.
 */
static void
compute_delta_dist(double rayDirX, double rayDirY,
                   double *deltaDistX, double *deltaDistY)
{
    if (rayDirX == 0.0)
        *deltaDistX = 1000000.0;   /* acts like "infinity" for vertical rays */
    else
        *deltaDistX = fabs(1.0 / rayDirX);

    if (rayDirY == 0.0)
        *deltaDistY = 1000000.0;   /* acts like "infinity" for horizontal rays */
    else
        *deltaDistY = fabs(1.0 / rayDirY);
}

/*
 * Initialize step direction (stepX / stepY) and the initial side distances
 * (sideDistX / sideDistY) used by the DDA loop.
 */
static void
init_step_and_sidedist(double posX, double posY, int mapX, int mapY,
                       double rayDirX, double rayDirY,
                       double deltaDistX, double deltaDistY,
                       int *stepX, int *stepY,
                       double *sideDistX, double *sideDistY)
{
    if (rayDirX < 0.0)
    {
        *stepX = -1;
        *sideDistX = (posX - (double)mapX) * deltaDistX;
    }
    else
    {
        *stepX = 1;
        *sideDistX = ((double)mapX + 1.0 - posX) * deltaDistX;
    }

    if (rayDirY < 0.0)
    {
        *stepY = -1;
        *sideDistY = (posY - (double)mapY) * deltaDistY;
    }
    else
    {
        *stepY = 1;
        *sideDistY = ((double)mapY + 1.0 - posY) * deltaDistY;
    }
}

/*
 * Perform the DDA stepping until a wall is hit.
 * This updates mapX/mapY to the hit cell and writes which side was hit (0 = x-side, 1 = y-side).
 * Out-of-bounds map accesses are treated as walls.
 */
static void
perform_dda(t_parsed_data *pd,
            int *mapX, int *mapY,
            double *sideDistX, double *sideDistY,
            double deltaDistX, double deltaDistY,
            int stepX, int stepY,
            int *side)
{
    while (1)
    {
        if (*sideDistX < *sideDistY)
        {
            *sideDistX += deltaDistX;
            *mapX += stepX;
            *side = 0;
        }
        else
        {
            *sideDistY += deltaDistY;
            *mapY += stepY;
            *side = 1;
        }

        /* safe char read: if out-of-bounds treat as wall */
        char c = '1';
        if (*mapY >= 0 && pd->map_grid[*mapY] && *mapX >= 0 && pd->map_grid[*mapY][*mapX])
            c = pd->map_grid[*mapY][*mapX];
        if (c != '0')
            break;
    }
}

/*
 * Compute the perpendicular wall distance (distance from player to the wall)
 * using the final mapX/mapY and which side was hit.
 * Returns a small positive number if division by zero would occur.
 */
static double
compute_perp_wall_dist(int side, int mapX, int mapY,
                       double posX, double posY,
                       int stepX, int stepY,
                       double rayDirX, double rayDirY)
{
    double perpWallDist;

    if (side == 0)
    {
        if (rayDirX == 0.0)
            perpWallDist = 0.000001; /* tiny value instead of dividing by zero */
        else
            perpWallDist = ((double)mapX - posX + (1 - stepX) / 2.0) / rayDirX;
    }
    else
    {
        if (rayDirY == 0.0)
            perpWallDist = 0.000001; /* tiny value instead of dividing by zero */
        else
            perpWallDist = ((double)mapY - posY + (1 - stepY) / 2.0) / rayDirY;
    }

    if (perpWallDist <= 0.0)
        perpWallDist = 0.000001;

    return perpWallDist;
}

/*
 * Main raycast renderer.
 * Iterates over screen columns, casts rays, runs DDA, computes wall slice and draws sky/wall/floor.
 */
void
raycast_render(t_parsed_data *pd)
{
    int w = pd->screen->width;
    int h = pd->screen->height;
    double posX = pd->player.bpos.x;
    double posY = pd->player.bpos.y;
    double dirX = pd->player.bdir.x;
    double dirY = pd->player.bdir.y;
    double planeX = pd->player.camera_plane.dir.x;
    double planeY = pd->player.camera_plane.dir.y;
    int x = 0;

    while (x < w)
    {
        double cameraX = 2.0 * (double)x / (double)w - 1.0;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = (int)posX;
        int mapY = (int)posY;

        double sideDistX;
        double sideDistY;
        double deltaDistX;
        double deltaDistY;

        compute_delta_dist(rayDirX, rayDirY, &deltaDistX, &deltaDistY);

        int stepX;
        int stepY;
        int side = 0;

        init_step_and_sidedist(posX, posY, mapX, mapY,
                               rayDirX, rayDirY,
                               deltaDistX, deltaDistY,
                               &stepX, &stepY,
                               &sideDistX, &sideDistY);

        perform_dda(pd, &mapX, &mapY, &sideDistX, &sideDistY,
                    deltaDistX, deltaDistY, stepX, stepY, &side);

        double perpWallDist = compute_perp_wall_dist(side, mapX, mapY,
                                                     posX, posY, stepX, stepY,
                                                     rayDirX, rayDirY);

        int lineHeight = (int)((double)h / perpWallDist);
        int drawStart = -lineHeight / 2 + h / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if (drawEnd >= h)
            drawEnd = h - 1;

        uint32_t sky_col = 0x0018B8FF;     /* sky */
        uint32_t floor_col = 0x0022B14C;   /* floor */
        uint32_t wall_col;
        if (side == 1)
            wall_col = 0x007F7F7F;   /* darker wall when Y-side */
        else
            wall_col = 0x00FFFFFF;   /* brighter wall when X-side */

        int y = 0;
        while (y < drawStart)
            mlx_put_pixel(pd->screen, x, y++, sky_col);
        while (y <= drawEnd)
            mlx_put_pixel(pd->screen, x, y++, wall_col);
        while (y < h)
            mlx_put_pixel(pd->screen, x, y++, floor_col);

        x++;
    }

    /* push image to window (MLX42 style) */
    // mlx_image_to_window(pd->mlx, pd->screen, 0, 0);
}

