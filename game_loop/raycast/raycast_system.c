#include "../../cube.h"

// just a helper for now
static void draw_camera_plane_point(t_parsed_data *pd)
{
    // logic for plane
    (void)pd;
}

void	raycast_system(t_parsed_data *pd)
{
    int x;
    int y;
    // update_raycast_data
    update_raycast_data(pd);
    draw_camera_plane_point(pd);
    // for each pixel in the screen send a ray from player pos.
    y = 0;
    while (y < WIDTH)
    {
        x = 0;
        while (x < HEIGHT)
        {
            x++;
        }
        y++;
    }
    (void)pd;
}
