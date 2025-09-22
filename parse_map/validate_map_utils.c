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

size_t	arg_count(char **argv)
{
	size_t	argc;

	argc = 0;
    if (!argv)
    {
        return (0);
    }
	while (argv[argc])
		argc++;
	return (argc);
}


static bool valid_texture_string(char *str)
{
    char    **args;

    if (ft_strlen(str) < 1)
        return (false);
    args = tab_split(str, " \t");
    if(arg_count(args) != 2)
        return (false);
    return (true);
}

static void extracting_each(t_texture *texture, char *str)
{
    if (texture->already_extracted)
    {
        print_error("Error\nNo Double Textures.\n");
        mind_free_all(EXIT_FAILURE);
    }
    texture->path = tab_split(str, " \t")[1];
    texture->already_extracted = true;
}

static void extract_texture(char *str, char first, char second,t_cube *cube) 
{
    if (first == 'N' && second == 'O')
        extracting_each(&cube->pd.txtr_no, str);
    else if (first == 'S' && second == 'O')
        extracting_each(&cube->pd.txtr_so, str);
    else if (first == 'W' && second == 'E')
        extracting_each(&cube->pd.txtr_we, str);
    else if (first == 'E' && second == 'A')
        extracting_each(&cube->pd.txtr_ea, str);
}

void validate_textures(char **map_file, t_cube *cube)
{
    int i;

    i = 0;
    while(map_file[i])
    {
        if (validate_floor_roof(map_file[i]))
            extarct_floor_roof(map_file[i], cube);
        if (valid_texture_string(map_file[i]))
            extract_texture(map_file[i], map_file[i][0], map_file[i][1], cube);
        if (valid_grid_chars(map_file[i]) && !validate_floor_roof(map_file[i]) && !valid_texture_string(map_file[i]))
        {
            extract_map(map_file, &i, cube);
            break;
        }
        if ((map_file[i] && map_file[i][0] != '\0') 
            && !valid_grid_chars(map_file[i]) 
            && !validate_floor_roof(map_file[i]) 
            && !valid_texture_string(map_file[i]))
        {
            print_error("Error\nInvalid Parameters In File.\n");
            mind_free_all(EXIT_FAILURE);
        }
        i++;
    }
    // check if all four textures have been extracted.
}
