#include "../cube.h"

bool is_door(char c)
{
    if (c == 'D')
        return (true);
    return (false);
}

// Check if a given cell is empty (0) safely inside the map
static bool is_clear(t_parsed_data *pd, int x, int y)
{
    if (x < 0 || y < 0 || y >= pd->level.max_y || x >= pd->level.max_x)
        return (false);
    return (pd->map_grid[y][x] == '0');
}

// Check if the door has exactly two opposite clear sides
bool only_two_clear_sides(t_parsed_data *pd, int x, int y)
{
    bool up    = is_clear(pd, x, y - 1);
    bool down  = is_clear(pd, x, y + 1);
    bool left  = is_clear(pd, x - 1, y);
    bool right = is_clear(pd, x + 1, y);

    // Case 1: Vertical door (open up & down, closed left & right)
    if (up && down && !left && !right)
        return (true);

    // Case 2: Horizontal door (open left & right, closed up & down)
    if (left && right && !up && !down)
        return (true);

    // Otherwise, invalid door placement
    return (false);
}

bool validate_door(t_parsed_data *pd, int x, int y)
{
    if (x <= 0 || x >= pd->level.max_x || y <= 0 || y >= pd->level.max_y)
        return (false);
    if (pd->map_grid[y][x + 1] == '1' || pd->map_grid[y][x - 1] == '1')
        if (pd->map_grid[y + 1][x] != '0' && pd->map_grid[y - 1][x] != '0')
            return (false);
    else if (pd->map_grid[y + 1][x] == '1' || pd->map_grid[y - 1][x] == '1')
        if (pd->map_grid[y][x + 1] != '0' && pd->map_grid[y][x - 1] != '0')
            return (false);
    if (!only_two_clear_sides(pd, x, y))
        return (false);

    return (true);
}
