/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 18:06:29 by aramos-r          #+#    #+#             */
/*   Updated: 2026/06/09 17:42:56 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_render.h"
#include "rtapp.h"

static uint32_t	*get_pixel_ptr(uint32_t *img, int x, int y)
{
	return (&img[y * W_WIDTH + x]);
}

int	get_next_tile(t_tile_queue *queue, t_tile *tile)
{
	if (queue->current_y >= W_HEIGHT)
		return (0);
	tile->x_start = queue->current_x;
	tile->y_start = queue->current_y;
	tile->x_end = queue->current_x + TILE_SIZE;
	tile->y_end = queue->current_y + TILE_SIZE;
	tile->get_pixel_ptr = &get_pixel_ptr;
	if (tile->x_end > W_WIDTH)
		tile->x_end = W_WIDTH;
	if (tile->y_end > W_HEIGHT)
		tile->y_end = W_HEIGHT;
	queue->current_x += TILE_SIZE;
	if (queue->current_x >= W_WIDTH)
	{
		queue->current_x = 0;
		queue->current_y += TILE_SIZE;
	}
	return (1);
}

t_hit	new_hit(void)
{
	t_hit	hit;

	hit.obj = NULL;
	hit.distance = INFINITY;
	return (hit);
}

t_tile_queue	new_tile_queue(void)
{
	t_tile_queue	queue;

	queue.current_x = 0;
	queue.current_y = 0;
	return (queue);
}
