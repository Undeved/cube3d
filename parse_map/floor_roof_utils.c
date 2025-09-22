#include "../cube.h"

static int	flow_check(long pow, char c, int s)
{
	long	next_pow;

	next_pow = (pow * 10) + (c - 48);
	if ((s == -1 && next_pow < pow) || (s == 1 && next_pow < pow))
	{
		if (s == -1)
			return (0);
		else
			return (-1);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	pow;
	int		s;

	i = 0;
	s = 1;
	pow = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (flow_check(pow, str[i], s) != 1)
			return (flow_check(pow, str[i], s));
		pow = (pow * 10) + (str[i] - 48);
		i++;
	}
	return ((int)pow * s);
}

bool is_num(char *str)
{
    int i;
    int num;

    i = 0;
    while (str[i])
    {
        if (!(str[i] <= '9' && str[i] >= '0'))
            return (false);
        i++;
    }
    num = ft_atoi(str);
    if (!(num <= 255 && num >=0))
        return (false);
    return (true);
}
