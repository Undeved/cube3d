/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:30:53 by oimzilen          #+#    #+#             */
/*   Updated: 2025/10/14 21:59:16 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void print_parsed_data(t_parsed_data *pd)
{
    printf("file descriptor --> %d\n", pd->fd);
    printf("north texture path --> %s\nalready extracted = %d\n", pd->txtr_no.path, pd->txtr_no.already_extracted);
    printf("south texture path --> %s\nalready extracted = %d\n", pd->txtr_so.path, pd->txtr_so.already_extracted);
    printf("west texture path --> %s\nalready extracted = %d\n", pd->txtr_we.path, pd->txtr_we.already_extracted);
    printf("east texture path --> %s\nalready extracted = %d\n", pd->txtr_ea.path, pd->txtr_ea.already_extracted);

    printf("floor --> already extracted %d\nR:%d, G:%d, B:%d\n", pd->floor.already_extracted, pd->floor.r, pd->floor.g, pd->floor.b);
    printf("ceiling --> already extracted %d\nR:%d, G:%d, B:%d\n", pd->roof.already_extracted, pd->roof.r, pd->roof.g, pd->roof.b);
    puts("Map Grid");
    int i = 0;
    int j = 0;
    while (pd->map_grid[i])
    {
        j = 0;
        write(1, "[", 1);
        while (pd->map_grid[i][j])
        {
            write(1, &pd->map_grid[i][j], 1);
            if (pd->map_grid[i][j] && pd->map_grid[i][j + 1])
                write(1, ", ", 2);
            j++;
        }
        write(1, "]\n", 2);
        i++;
    }
    printf("level max_x  %d\n", pd->level.max_x);
    printf("level max_y  %d\n", pd->level.max_y);
    printf("Player Data\n");
    printf("player x pos %d\n", pd->player.pos.x);
    printf("player y pos %d\n", pd->player.pos.y);
    printf("player direction %c\n", pd->player.dir);

    printf("Enemies (%d total):\n", pd->enemy_count);
    for (int e = 0; e < pd->enemy_count; e++)
    {
        printf("Enemy[%d]:\n", e);
        printf("  pos: x = %d, y = %d\n", pd->enemies[e].pos.x, pd->enemies[e].pos.y);
        printf("  dir: x = %f, y = %f\n", pd->enemies[e].dir.x, pd->enemies[e].dir.y);
        if (pd->enemies[e].type == 0)
            printf("  type: -42 Skin Walker\n");
        else if (pd->enemies[e].type == 1)
            printf("  type: Memory Leak\n");
        else if (pd->enemies[e].type == 2)
            printf("  type: SEGV\n");
        printf("  health: %d\n", pd->enemies[e].health);
        printf("  damage: %d\n", pd->enemies[e].damage);
        printf("  dead: %s\n", pd->enemies[e].dead ? "true" : "false");
    }
}

int main(int argc, char **argv)
{
    t_cube  cube;

    evaluate_input(argc, argv);
    parse_map(argv[1], &cube);
    // print_parsed_data(&cube.pd);
    game_loop(&cube.pd);
    // print_argv(cube.pd.map_file);

    // testing window creation
    // basic_game_loop();

    return (mind_free_all(EXIT_SUCCESS), EXIT_SUCCESS);
}
 