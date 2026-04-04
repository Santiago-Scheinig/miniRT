/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:58:29 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/04 18:38:49 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_render.h"
#include <stdio.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
#endif

static void	print_header(void)
{
	printf("\e[1;34m====================\n");
	printf("   RENDER TESTER\n");
	printf("====================\e[0m\n");
}

static void	test_function( int (*f)(void), char* name )
{
	if (f() == 0)
		printf("\e[0;32m%s: OK\n\e[0m", name);
	else
		printf("\e[0;31m%s: FAIL\n\e[0m", name);
}

static int  test_new_tile_queue(void)
{
    t_tile_queue queue = new_tile_queue();
    if (queue.current_x != 0 || queue.current_y != 0)
        return (1);
    return (0);
}

static int  test_get_next_tile(void)
{
    t_tile_queue queue = new_tile_queue();
    t_tile tile;

    if (!get_next_tile(&queue, &tile))
        return (1);
    if (tile.x_start != 0 || tile.y_start != 0 || tile.x_end != TILE_SIZE || tile.y_end != TILE_SIZE)
        return (1);
    
    for (int i = 0; i < 135; i++)
    {
        if (!get_next_tile(&queue, &tile))
            return (1);
    }
    if (tile.x_start != 240 || tile.y_start != 16 || tile.x_end != 256 || tile.y_end != 32)
        return (1);
    return (0);
}

int main(void)
{
	int (*tests[])(void) = {
		test_new_tile_queue,
		test_get_next_tile
	};
	char* test_names[] = {
        "test_new_tile_queue",
        "test_get_next_tile"
	};
	print_header();
	for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
		test_function(tests[i], test_names[i]);
	return (0);
}
