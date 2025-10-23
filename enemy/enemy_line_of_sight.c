#include "../cube.h"

bool check_line_path(t_parsed_data *pd, t_bpos start, t_bpos step,
        double max_dist)
{
    t_bpos  current;
    double  dist;
    int     map_x;
    int     map_y;

    current.x = start.x;
    current.y = start.y;
    dist = 0.0;
    while (dist < max_dist)
    {
        current.x += step.x;
        current.y += step.y;
        dist += sqrt(step.x * step.x + step.y * step.y);
        if (dist >= max_dist)
            break ;
        map_x = (int)current.x;
        map_y = (int)current.y;
        if (map_y < 0 || map_y >= pd->level.max_y)
            return (false);
        if (map_x < 0 || map_x >= pd->level.max_x)
            return (false);
        if (pd->map_grid[map_y][map_x] == '1' || pd->map_grid[map_y][map_x] == 'D')
            return (false);
    }
    return (true);
}

bool has_line_of_sight(t_parsed_data *pd, t_bpos start, t_bpos end)
{
    t_bpos  delta;
    t_bpos  step;
    double  max_dist;

    delta.x = end.x - start.x;
    delta.y = end.y - start.y;
    max_dist = sqrt(delta.x * delta.x + delta.y * delta.y);
    step.x = delta.x / (max_dist * 4.0);
    step.y = delta.y / (max_dist * 4.0);
    return (check_line_path(pd, start, step, max_dist));
}
