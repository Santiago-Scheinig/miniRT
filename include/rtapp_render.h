/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_render.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:56:49 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/12 20:43:46 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_RENDER_H
# define RTAPP_RENDER_H
# define TILE_SIZE 16

/*--------------------------------------------------------------------------*/
/*--------------------------------STRUCTURES--------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Represents a rectangular tile section of the render buffer.
 * @note Tiles divide the screen into smaller sections for efficient
 * rendering, enabling multi-threaded processing where each thread
 * works on an independent tile without overlap.
 */
typedef struct s_tile
{
	int x_start; // Starting x-coordinate of the tile, inclusive.
	int y_start; // Starting y-coordinate of the tile, inclusive.
	int x_end;   // Ending x-coordinate of the tile, exclusive.
	int y_end;   // Ending y-coordinate of the tile, exclusive.
}   t_tile;

/**
 * Tracks the next tile to be dispatched in the render queue.
 * @note In multi-threaded rendering, threads read and advance this
 * queue atomically to claim the next unrendered tile without overlap.
 */
typedef struct s_tile_queue
{
	int	current_x; // X coordinate of the next tile to be rendered.
	int	current_y; // Y coordinate of the next tile to be rendered.
}   t_tile_queue;

/*--------------------------------------------------------------------------*/
/*--------------------------------UTILITIES---------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Initializes a tile queue starting at the top-left of the screen.
 * @return A T_TILE_QUEUE with current_x and current_y set to 0.
 */
t_tile_queue	new_tile_queue(void);

/**
 * Fills the next tile from the queue and advances the queue position.
 * @param queue The T_TILE_QUEUE tracking the current render position.
 * @param tile The T_TILE to fill with the next section's coordinates.
 * @return 1 if a valid tile was written to TILE, 0 if the queue is
 * exhausted and all tiles have been dispatched.
 * @note Tile boundaries are clamped to SCREEN_WIDTH and SCREEN_HEIGHT
 * to handle edge tiles that don't align to TILE_SIZE. The queue advances
 * left to right, then top to bottom across the screen.
 */
int				get_next_tile(t_tile_queue *queue, t_tile *tile);

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif