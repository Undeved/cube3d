#include "../cube.h"

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*ptr;

	ptr = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
