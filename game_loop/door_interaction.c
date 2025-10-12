#include "../cube.h"

void interact_with_door(t_parsed_data *pd)
{
    static bool e_was_pressed = false;
    int px = (int)pd->player.bpos.x;
    int py = (int)pd->player.bpos.y;
    char **map = pd->map_grid;

    // check if E is pressed
    bool e_pressed = pd->keys.pressed[MLX_KEY_E];

    // trigger only once when key changes from not pressed → pressed
    if (e_pressed && !e_was_pressed)
    {
        // try to open or close nearby doors
        if (map[py][px + 1] == 'D')
            map[py][px + 1] = 'O';
        else if (map[py][px + 1] == 'O')
            map[py][px + 1] = 'D';

        if (map[py][px - 1] == 'D')
            map[py][px - 1] = 'O';
        else if (map[py][px - 1] == 'O')
            map[py][px - 1] = 'D';

        if (map[py + 1][px] == 'D')
            map[py + 1][px] = 'O';
        else if (map[py + 1][px] == 'O')
            map[py + 1][px] = 'D';

        if (map[py - 1][px] == 'D')
            map[py - 1][px] = 'O';
        else if (map[py - 1][px] == 'O')
            map[py - 1][px] = 'D';
    }

    // save current state for next frame
    e_was_pressed = e_pressed;
}