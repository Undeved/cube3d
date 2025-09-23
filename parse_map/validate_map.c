#include "../cube.h"

static bool has_nl(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (true);
        i++;
    }
    return (false);
}

char    **trim_newlines(char **old_argv)
{
    char    **new_argv;
    int     argc;
    int     i;

    argc = arg_count(old_argv);
    new_argv = allocate_gc(malloc(sizeof(char *) * (argc + 1)));
    i = 0;
    while (old_argv[i])
    {
        if (has_nl(old_argv[i]))
            new_argv[i] = allocate_gc(ft_substr(old_argv[i], 0 , ft_strlen(old_argv[i]) - 1));
        else
            new_argv[i] = old_argv[i];
        i++;
    }
    new_argv[i] = NULL;
    return (new_argv);
}

void    validate_map(char **map_file, t_cube *cube)
{
    validate_params(map_file, cube);
    if(cube->pd.player_count != 1)
    {
        print_error("Error\nInvalid Player Parameter.\n");
        mind_free_all(EXIT_FAILURE);
    }
    closed_bounds(cube);
}
