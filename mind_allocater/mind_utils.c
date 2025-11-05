#include "../cube.h"

t_parsed_data	**get_pd(void)
{
	static t_parsed_data	*pd = NULL;

	return (&pd);
}

void	set_pd(t_parsed_data *new_pd)
{
	t_parsed_data	**pd_ptr;

	pd_ptr = get_pd();
	*pd_ptr = new_pd;
}
