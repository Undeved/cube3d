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

void escape_handler(mlx_key_data_t keydata, void* param)
{
    mlx_t   *mlx;

    mlx = param;
    (void)mlx;
    if (keydata.key == MLX_KEY_ESCAPE)
        mind_free_all(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    t_cube  cube;
    mlx_t   *mlx;

    evaluate_input(argc, argv);
    parse_map(argv[1], &cube);
    // print_argv(cube.pd.map_file);

    // testing window creation
    mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
    if (!mlx)
        mind_free_all(EXIT_FAILURE);
    mlx_key_hook(mlx, escape_handler, mlx);
    mlx_loop_hook(mlx, simple_raycast,mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    //--- done testing

    return (EXIT_SUCCESS);
}