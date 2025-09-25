#include "../../cube.h"

static void camera_plane(t_parsed_data *pd)
{
    pd->player.camera_plane.pos.x = pd->player.bdir.x * SCALER;
    pd->player.camera_plane.pos.y = pd->player.bdir.y * SCALER;
    pd->player.camera_plane.dir.x = pd->player.bdir.y;
    pd->player.camera_plane.dir.y = -pd->player.bdir.x;
}

void    update_raycast_data(t_parsed_data *pd)
{
    camera_plane(pd);
}
