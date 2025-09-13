#include "cube.h"

void    print_argv(char **argv)
{
    int i;

    i = 0;
    if (!argv)
        return ;
    while (argv[i])
    {
        write(1, argv[i], ft_strlen(argv[i]));
        i++;
    }
}