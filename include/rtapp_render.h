/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_render.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:56:49 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/23 19:57:42 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_RENDER_H
# define RTAPP_RENDER_H
# include "rtapp.h"
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
	int			x_start;	// Starting x-coordinate of the tile, inclusive.
	int			y_start;	// Starting y-coordinate of the tile, inclusive.
	int			x_end;		// Ending x-coordinate of the tile, exclusive.
	int			y_end;		// Ending y-coordinate of the tile, exclusive.
	uint32_t	*(*get_pixel_ptr)(uint32_t *img, int x, int y);
}	t_tile;

/**
 * Tracks the next tile to be dispatched in the render queue.
 * @note In multi-threaded rendering, threads read and advance this
 * queue atomically to claim the next unrendered tile without overlap.
 */
typedef struct s_tile_queue
{
	int	current_x; // X coordinate of the next tile to be rendered.
	int	current_y; // Y coordinate of the next tile to be rendered.
}	t_tile_queue;

/**
 * @brief Represents a ray-object intersection hit, containing all necessary
 * information for shading calculations.
 * @param obj A reference to the object that was hit by the ray.
 * @param pos The world-space position where the ray intersects the object.
 * @param distance The distance from the ray origin to the hit position.
 * @param surf_normal The surface normal at the hit position, used for
 * lighting calculations.
 */
typedef struct s_hit
{
	t_object	*obj;
	t_vector	pos;
	double		distance;
	t_vector	surf_normal;
}	t_hit;

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

/**
 * @brief Casts a ray into the scene and finds the closest intersection hit.
 * @param ray The T_RAY to cast into the scene.
 * @param objs An array of T_OBJECTs representing the scene geometry.
 * @return A T_HIT containing the closest intersection information. If no
 * intersection occurs, the T_HIT will have obj set to NULL and distance set
 * to INFINITY.
 */
t_hit			get_hit_from_ray(t_ray ray, t_list *objs);

/**
 * @brief Computes the color at a ray-object intersection point using the
 * Phong reflection model, accounting for all light sources in the scene.
 * @param hit The T_HIT containing the intersection information for shading.
 * @param objects The list of T_OBJECTs in the scene for shadow ray testing.
 * @param app The T_RTAPP containing the scene's ambient light and point lights.
 * @return A T_VECTOR representing the final RGB color at the hit point, with
 * each component normalized to the 0.0-1.0 range.
 */
t_vector		get_color_at_hit(
					t_hit hit,
					t_list *objs,
					t_rtapp *app
					);

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif