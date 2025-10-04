#include "../../cube.h"

static	int	ft_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr == -2147483648)
		return (11);
	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
	}
	if (nbr == 0)
		len++;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static char	*max_int(char *str)
{
	char	*tmp;
	int		i;

	tmp = "-2147483648";
	i = 0;
	while (tmp[i])
	{
		str[i] = tmp[i];
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;

	len = ft_len(n);
	s = (char *) malloc ((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[len--] = 0;
	if (n == 0)
		s[0] = '0';
	if (n == -2147483648)
		return (max_int(s));
	if (n < 0)
	{
		n = -n;
		s[0] = '-';
	}
	while (n != 0)
	{
		s[len--] = (n % 10) + 48;
		n /= 10;
	}
	return (s);
}
