#include "../cube.h"

void interact_with_door(t_parsed_data *pd)
{
    int px = (int)pd->player.bpos.x;
    int py = (int)pd->player.bpos.y;
    char **map = pd->map_grid;

    // make a cooldown to press E
    if (!pd->keys.pressed[MLX_KEY_E])
        return;

    // Right
    if (map[py][px + 1] == 'D')
        map[py][px + 1] = 'O'; // Open the door
    else if (map[py][px + 1] == 'O')
        map[py][px + 1] = 'D'; // Close the door
    // Left
    else if (map[py][px - 1] == 'D')
        map[py][px - 1] = 'O';
    else if (map[py][px - 1] == 'O')
        map[py][px - 1] = 'D';
    // Down
    else if (map[py + 1][px] == 'D')
        map[py + 1][px] = 'O';
    else if (map[py + 1][px] == 'O')
        map[py + 1][px] = 'D';
    // Up
    else if (map[py - 1][px] == 'D')
        map[py - 1][px] = 'O';
    else if (map[py - 1][px] == 'O')
        map[py - 1][px] = 'D';
}
