#include "../cube.h"

bool valid_grid_chars(char *str, int *player_count, bool map_grid)
{
    int i;

    i = 0;
    if (str[0] == '\0')
        return (false);
    while (str[i])
    {
        if ((str[i] == 'N' || str[i] == 'S' || str[i] == 'E'  || str[i] == 'W') && map_grid)
        {
            (*player_count)++;
        }
        if (str[i] != '1' && str[i] != '0' && str[i] != 'N'
            && str[i] != 'S' && str[i] != 'E' 
            && str[i] != 'W' && str[i] != ' ')
            return (false);
        i++;
    }
    return (true);
}

static bool map_is_last(t_cube *cube)
{
    if (!cube->pd.txtr_no.already_extracted 
        || !cube->pd.txtr_ea.already_extracted 
        ||!cube->pd.txtr_we.already_extracted 
        || !cube->pd.txtr_so.already_extracted)
        return (false);
    if (!cube->pd.floor.already_extracted 
        || !cube->pd.roof.already_extracted)
        return (false);
    return (true);
}

void    extract_map(char **map_file, int *i, t_cube *cube)
{
    int j;

    if (!map_is_last(cube))
    {
        print_error("Error\nMap Grid Should Be The Last Parameter.\n");
        mind_free_all(EXIT_FAILURE);
    }
    cube->pd.map_grid = allocate_gc(malloc(sizeof(char *) 
        *(arg_count(map_file + *i) + 1)));
    j = 0;
    while (map_file[*i])
    {
        if (valid_grid_chars(map_file[*i], &cube->pd.player_count, true))
            cube->pd.map_grid[j] = map_file[*i];
        else
        {
            print_error("Error\nInvalid Chars In Map Grid.\n");
            mind_free_all(EXIT_FAILURE);
        }
        (*i)++;
        j++;
    }
    cube->pd.map_grid[j] = NULL;
}
