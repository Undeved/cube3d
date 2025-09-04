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


    (void)argv;
    evaluate_input(argc, argv);

    // ------------------------------------------------
    mlx_t *mlx;

    // Initialize the mlx42 library and create a window 800x600
    mlx = mlx_init(800, 600, "My MLX42 Window", true);
    if (!mlx)
        return (print_error("MLX failed.\n"), EXIT_FAILURE);

    // Main loop
    mlx_loop(mlx);

    // Clean up (never reached in this minimal example)
    mlx_terminate(mlx);
    //---------------------------------------------------

    return (EXIT_SUCCESS);
}