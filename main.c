/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:30:53 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/27 22:36:33 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int main(int argc, char **argv)
{
    t_cube  cube;

    evaluate_input(argc, argv);
    parse_map(argv[1], &cube);
    print_argv(cube.pd.map_file);

    return (EXIT_SUCCESS);
}