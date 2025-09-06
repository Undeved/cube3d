#include "../cube.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
    if (!s1 || !s2)
    {
        return (1);
    }
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2 [i]);
		}
		i++;
	}
	return (0);
}

static char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	a;
	char	*ptr;

	i = 0;
	ptr = NULL;
	a = (char ) c;
	while (s[i])
	{
		if (s[i] == a)
		{
			ptr = (char *) s + i;
		}
		i++;
	}
	if (s[i] == a)
		ptr = ((char *) s + i);
	return (ptr);
}

void    evaluate_input(int argc, char **argv)
{
    if (argc != 2)
    {
        print_comm("Usage ./cub3D <map_name>.cub\n");
        exit(EXIT_SUCCESS);
    }
    if (ft_strcmp(ft_strrchr(argv[1], '.'), ".cub") != 0)
    {
        print_comm("Invalid Map Name.\n");
        exit(EXIT_SUCCESS);
    }
}
