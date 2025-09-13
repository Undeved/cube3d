#include "../cube.h"

char	*ft_strchr(char	*s, int c)
{
	int		i;
	char	a;

	i = 0;
	a = (char) c;
	while (s[i])
	{
		if (a == s[i])
			return ((char *)s + i);
		i++;
	}
	if (a == s[i])
		return ((char *)s + i);
	return (0);
}

void north_texture(char **map_file)
{
    int i;
    int count;
    int index;

    i = 0;
    index = -1;
    count = 0;
    while(map_file[i])
    {
        // make sshift solution i cut NO perfectly i need to cut until space.
        if (ft_strcmp(allocate_gc(gnl_ft_substr(ft_strchr(map_file[i],
                'N'), 0, 2)), "NO") == 0)
        {
            count++;
            index = map_file[i] - ft_strchr(map_file[i], 'N');
        }
        i++;
    }
    if (index == 0)
    {
        if (count == 0)
        {
            print_error("Error\nNo North Texture.\n");
            mind_free_all(EXIT_FAILURE);
        }
        else if (count > 1)
        {
            print_error("Error\nDuplicate North Texture.\n");
            mind_free_all(EXIT_FAILURE);
        }
    }
    else
    {
        print_error("Error\nNorth Texture Usage <NO ...>.\n");
        mind_free_all(EXIT_FAILURE);
    }
}
