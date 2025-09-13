#include "../cube.h"

static void closer(int *fd)
{
    if (*fd != -1)
        close(*fd);
    *fd = -1;
}

static void read_map_file(char *map_path, t_cube *cube)
{
    char    *line;
    int     count;
    int     i;

    cube->pd.fd = open(map_path, O_RDONLY);
    if (cube->pd.fd == -1)
        mind_free_all(EXIT_FAILURE); // print error no such file
    count = 0;
    line = get_next_line(cube->pd.fd);
    while (line != NULL)
    {
        count++;
        free(line);
        line = get_next_line(cube->pd.fd);
    }
    closer(&cube->pd.fd);
    if (count == 0)
        mind_free_all(EXIT_FAILURE);
    cube->pd.map_file = allocate_gc(malloc(sizeof(char *) * (count + 1)));
    cube->pd.fd = open(map_path, O_RDONLY);
    if (cube->pd.fd == -1)
        mind_free_all(EXIT_FAILURE);
    i = 0;
    line = get_next_line(cube->pd.fd); 
    while (line != NULL)
    {
        cube->pd.map_file[i] = allocate_gc(ft_strdup(line));
        free(line);
        if (!cube->pd.map_file[i])
        {
            closer(&cube->pd.fd);
            mind_free_all(EXIT_FAILURE);
        }
        i++;
        line = get_next_line(cube->pd.fd);
    }
    cube->pd.map_file[i] = NULL;
    closer(&cube->pd.fd);
}

void    parse_map(char *map_path, t_cube *cube)
{
    cube->map_path = allocate_gc(ft_strdup(map_path));
    read_map_file(cube->map_path, cube);
    validate_map(cube->pd.map_file);
}

