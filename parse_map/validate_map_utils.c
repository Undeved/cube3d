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

void north_texture(char **map_file) // pass struct
{
    int i;
    int count;

    i = 0;
    count = 0;
    (void)count;
    while(map_file[i])
    {
        // code to validate NO texture and extract it.
        // validate if more than 2 chars
        // if first letter is N and second is O return true
        // if valid split , argc of this split should be exactly 2
        // second arg in split is path. extract it.
        i++;
    }
}
