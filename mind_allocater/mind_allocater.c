#include "../cube.h"

t_mind_alloc	**get_head(void)
{
	static t_mind_alloc	*gc = NULL;

	return (&gc);
}

int	add_to_gc(void *new_address)
{
	t_mind_alloc	**head;
	t_mind_alloc	*new_alloc;

	new_alloc = malloc(sizeof(t_mind_alloc));
	if (!new_alloc)
	{
		free(new_address);
		mind_free_all(EXIT_FAILURE);
	}
	head = get_head();
	new_alloc->ptr = new_address;
	new_alloc->free_at_end = false;
	new_alloc->next = *head;
	*head = new_alloc;
	return (EXIT_SUCCESS);
}

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

void	mind_free_all(int status)
{
	t_mind_alloc	**head;
	t_mind_alloc	*tmp;
	t_parsed_data   **pd;

	head = get_head();
	pd = get_pd();
	if (*pd && (*pd)->mlx)
	{
		delete_all_textures(*pd);
		mlx_terminate((*pd)->mlx);
	}
	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->ptr);
		free(*head);
		*head = tmp;
	}
	// close fd if forgot to close it somewhere very unlikely but safe check.
	*get_head() = NULL;
	exit(status);
}

void	*allocate_gc(void *ptr)
{
	if (!ptr)
		mind_free_all(EXIT_FAILURE);
	add_to_gc(ptr);
	return (ptr);
}
