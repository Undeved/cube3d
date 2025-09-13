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

void	mind_free_all(int status)
{
	t_mind_alloc	**head;
	t_mind_alloc	*tmp;

	head = get_head();
	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->ptr);
		free(*head);
		*head = tmp;
	}
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
