/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mind_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:39:51 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/09 22:40:16 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
