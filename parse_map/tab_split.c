#include "../cube.h"

static bool	in_set(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (true);
		i++;
	}
	return (false);
}

static size_t	ft_wordcount(const char *s, char *sep)
{
	size_t	wc;
	size_t	i;

	wc = 0;
	i = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		while (in_set(s[i], sep))
			i++;
		if (s[i])
			wc++;
		while (!in_set(s[i], sep) && s[i])
			i++;
	}
	return (wc);
}

static int	fill_word(const char *s, size_t i, char *sep, size_t *start)
{
	while (in_set(s[i], sep))
		i++;
	if (s[i])
		*start = i;
	while (!in_set(s[i], sep) && s[i])
		i++;
	return (i);
}

char	**tab_split(char *s, char *sep)
{
	size_t		i;
	size_t		j;
	size_t		start;
	char		**lst;

	if (!s)
		return (NULL);
	lst = allocate_gc(malloc ((ft_wordcount(s, sep) + 1) * sizeof(char *)));
	if (!lst)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		i = fill_word(s, i, sep, &start);
		if (s[i] || !in_set(s[i - 1], sep))
		{
			lst[j] = allocate_gc(ft_substr(s, start, i - start));
			j++;
		}
	}
	lst[j] = NULL;
	return (lst);
}
