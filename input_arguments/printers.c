#include "../cube.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    print_error(char *str)
{
    write(2, str, ft_strlen(str));
}

void    print_comm(char *str)
{
    write(1, str, ft_strlen(str));
}
