/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deceptive_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:42:49 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/16 03:59:44 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	garbage_error(void)
{
	print_error("Error: address sanitizer: ");
	print_error(RED);
	print_error("Buffer Overflow on unknown address 0x7ff4e2b83a20\n");
	print_error(RST);
	print_error("Error: detected memory corruption at: 0x");
	print_error("1c8d72f0\n");
	print_error("address 0x1c8d72f0 contains: ");
	print_error("0xdeadbeef\n");
	print_error("�^��*�^��@$�^+��%�^��@$�^���^��*�^��@$�^+��%�^��@$\n");
	print_error("�^���^��*�^��@$�^+�^��@$�^���^��*�^��@$�^+��%�^��@$�^��\n");
	print_error("expected valid heap object, got corrupted memory\n");
	print_error("memory region [0x1c8d7000,0x1c8d8000) is invalid\n");
}

void	leak_error(void)
{
	print_error("==12345== Memcheck, a memory error detector\n");
	print_error("==12345== Copyright (C) 2002-2017, ");
	print_error("and GNU GPL'd, by Julian Seward et al.\n");
	print_error("==12345== Using Valgrind-3.13.0 and LibVEX; ");
	print_error("rerun with -h for copyright info\n");
	print_error("==12345== Command: ./game\n\n");
	print_error("==12345== HEAP SUMMARY:\n");
	print_error("==12345==     in use at exit: 4,288 bytes in 7 blocks\n");
	print_error("==12345==   total heap usage: 1,234 allocs, 1,227 frees, ");
	print_error("89,432 bytes allocated\n\n");
	print_error("==12345== 512 bytes in 1 blocks are definitely lost ");
	print_error("in loss record 3 of 7\n");
	print_error("==12345==    at 0x4C2AB80: malloc ");
	print_error("(vg_replace_malloc.c:299)\n");
	print_error("==12345==    by 0x400A23: load_texture (texture.c:45)\n");
	print_error("==12345==    by 0x400C89: init_game (game.c:112)\n");
	print_error("==12345==    by 0x400F12: main (main.c:28)\n\n");
}

void	leak_error2(void)
{
	print_error("==12345== LEAK SUMMARY:\n");
	print_error("==12345==    definitely lost: 512 bytes in 1 blocks\n");
	print_error("==12345==    indirectly lost: 0 bytes in 0 blocks\n");
	print_error("==12345==      possibly lost: 1,024 bytes in 2 blocks\n");
	print_error("==12345==    still reachable: 2,752 bytes in 4 blocks\n");
	print_error("==12345==         suppressed: 0 bytes in 0 blocks\n\n");
	print_error("==12345== For counts of detected and suppressed errors, ");
	print_error("rerun with: -v\n");
	print_error("==12345== ERROR SUMMARY: 3 errors from 3 contexts ");
	print_error("(suppressed: 0 from 0)\n");
}

void	segmentation_fault_error(void)
{
	print_error("Segmentation fault at address: 0x7ffe42b83a20\n");
	print_error("Memory access violation:\n");
	print_error("0x7ffe42b83a00: 00 00 00 00 00 00 00 00 ");
	print_error("00 00 00 00 00 00 00 00\n");
	print_error("0x7ffe42b83a10: 00 00 00 00 00 00 00 00 ");
	print_error("00 00 00 00 00 00 00 00\n");
	print_error("0x7ffe42b83a20: 0F 0B 0B 0B 0B 0B 0B 0B ");
	print_error("0B 0B 0B 0B 0B 0B 0B 0B\n");
	print_error(RED);
	print_error("0x7ffe42b83a30: 0B 0B 0B 0B 0B 0B 0B 0B ");
	print_error("0B 0B 0B 0B 0B 0B 0B 0B\n");
	print_error("0x7ffe42b83a40: 0B 0B 0B 0B 0B 0B 0B 0B ");
	print_error("0B 0B 0B 0B 0B 0B 0B 0B\n");
	print_error("                     ^^\n");
	print_error(RST);
	print_error("Invalid memory access at marked location\n");
	print_error("Attempted to write to protected memory region\n");
}

void	print_death_message(t_parsed_data *pd, t_enemy *killer, bool deceptive)
{
	if (!deceptive)
	{
		print_comm(RED"Norminette: [KO], [KO], [KO], [KO], [KO], [KO]\n");
		print_comm("File: Game Over.exe"RST"\n");
		return ;
	}
	(void)pd;
	if (killer->type == FT_SKIN_WALKER)
		garbage_error();
	else if (killer->type == MEMORY_LEAK)
	{
		leak_error();
		leak_error2();
	}
	else
		segmentation_fault_error();
}
