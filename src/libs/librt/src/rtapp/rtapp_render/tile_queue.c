/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 18:06:29 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/04 18:19:36 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_render.h"
#include "rtapp.h"

t_tile_queue    new_tile_queue(void)
{
    t_tile_queue    queue;

    queue.current_x = 0;
    queue.current_y = 0;
    return (queue);
}

int get_next_tile(t_tile_queue *queue, t_tile *tile)
{
    if (queue->current_y >= SCREEN_HEIGHT)
        return (0);
    tile->x_start = queue->current_x;
    tile->y_start = queue->current_y;
    tile->x_end = queue->current_x + TILE_SIZE;
    tile->y_end = queue->current_y + TILE_SIZE;
    if (tile->x_end > SCREEN_WIDTH)
        tile->x_end = SCREEN_WIDTH;
    if (tile->y_end > SCREEN_HEIGHT)
        tile->y_end = SCREEN_HEIGHT;
    queue->current_x += TILE_SIZE;
    if (queue->current_x >= SCREEN_WIDTH)
    {
        queue->current_x = 0;
        queue->current_y += TILE_SIZE;
    }
    return (1);
}
