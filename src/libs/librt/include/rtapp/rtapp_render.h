/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_render.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:56:49 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/04 18:11:25 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_RENDER_H
# define RTAPP_RENDER_H
# define TILE_SIZE 16

/**
 * @brief Structure representing a tile in the rendering process.
 * This structure defines the starting and ending coordinates of a
 * tile, which is a portion of the image being rendered.
 * It is used to manage the rendering of the image in smaller sections,
 * allowing for more efficient processing and better performance,
 * especially in multi-threaded rendering scenarios.
 * @param x_start The starting x-coordinate of the tile.
 * @param y_start The starting y-coordinate of the tile.
 * @param x_end The ending x-coordinate of the tile.
 * @param y_end The ending y-coordinate of the tile.
 */
typedef struct s_tile
{
	int x_start;
	int y_start;
	int x_end;
	int y_end;
}   t_tile;

/**
 * @brief Structure representing the current position in the tile queue.
 * This structure is used to keep track of the next tile to be rendered
 * in the queue of tiles.
 * It contains the current x and y coordinates that indicate the position
 * of the next tile to be processed.
 * This is particularly useful in multi-threaded rendering, where multiple
 * threads may be working on different tiles simultaneously, and the queue
 * needs to be managed to ensure that all tiles are rendered correctly.
 * @param current_x The current x-coordinate in the tile queue.
 * @param current_y The current y-coordinate in the tile queue.
 */
typedef struct s_tile_queue
{
	int	current_x;
	int	current_y;
}   t_tile_queue;

/**
 * @brief Initializes the tile queue for rendering.
 * This function sets the initial position of the tile queue to the starting
 * coordinates (0, 0), which means that the rendering process will begin
 * from the top-left corner of the image.
 * @return A t_tile_queue structure initialized to the
 * starting position of the tile queue.
 */
t_tile_queue	new_tile_queue(void);

/**
 * @brief Retrieves the next tile from the tile queue.
 * @param queue A pointer to the tile queue from which to get the next tile.
 * @param tile A pointer to a t_tile structure where the next tile's coords.
 * will be stored.
 * @return An integer indicating whether there are more tiles to process
 * (1) or if the queue is empty (0).
 * @note This function updates the tile queue's current position
 * to the next tile after retrieving it.
 */
int				get_next_tile(t_tile_queue *queue, t_tile *tile);

#endif