#include "../cube.h"

static void closer(int *fd)
{
    if (*fd != -1)
        close(*fd);
    *fd = -1;
}

// refactor this and handle if gnl fails better.
static void read_map_file(char *map_path, t_cube *cube)
{
    char    *line;
    int     count;
    int     i;

    cube->pd.fd = open(map_path, O_RDONLY);
    if (cube->pd.fd == -1)
        mind_free_all(EXIT_FAILURE);
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

static void init_textures(t_cube *cube)
{
    cube->pd.txtr_no.path = NULL;
    cube->pd.txtr_so.path = NULL;
    cube->pd.txtr_we.path = NULL;
    cube->pd.txtr_ea.path = NULL;
    cube->pd.txtr_no.already_extracted = false;
    cube->pd.txtr_so.already_extracted = false;
    cube->pd.txtr_we.already_extracted = false;
    cube->pd.txtr_ea.already_extracted = false;
    cube->pd.txtr_no.dir = NORTH_TXT;
    cube->pd.txtr_so.dir = SOUTH_TXT;
    cube->pd.txtr_we.dir = WEST_TXT;
    cube->pd.txtr_ea.dir = EAST_TXT;
    cube->pd.floor.already_extracted = false;
    cube->pd.roof.already_extracted = false;
}

static void init_parsed_data(t_cube *cube)
{
    cube->pd.fd = -1;
    cube->pd.map_file = NULL;
    cube->pd.map_grid = NULL;
    init_textures(cube);
}

void    parse_map(char *map_path, t_cube *cube)
{
    init_parsed_data(cube);
    cube->map_path = allocate_gc(ft_strdup(map_path));
    read_map_file(cube->map_path, cube);
    cube->pd.map_file = trim_newlines(cube->pd.map_file);
    validate_map(cube->pd.map_file, cube);
}

