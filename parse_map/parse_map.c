#include "../cube.h"

void    parse_map(char *map_path, t_cube *cube)
{
    cube->map_path = ft_strdup(map_path);
}

