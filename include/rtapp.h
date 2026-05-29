/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:38:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 18:53:06 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_H
# define RTAPP_H

# include "libft.h"
# include "rtelm.h"
# include "rterr.h"
# include "rtmlx.h"
# include "rtmth.h"
# include "rtapp_debug.h"
# if BONUS
#  include <pthread.h>
#  define WORKER_COUNT 16
# endif

# ifndef DEV
#  define DEV 0
# endif

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
 * Represents the full state of the miniRT application.
 * @note objects and lights are NULL until parsed from the scene file.
 * camera.get_pixel_ray being NULL indicates the camera is uninitialized.
 * ambient.ratio being -1 indicates the ambient light is uninitialized.
 */
typedef struct s_rtapp
{
	uint32_t		*img;
	t_list			*objects;
	t_list			*lights;
	t_mlx			mlx;
	t_elem_camera	camera;
	t_elem_light_a	ambient;
	t_tile_queue	tile_queue;
# if BONUS
	t_rtlog			logfd;
	pthread_t		workers[WORKER_COUNT];
	pthread_mutex_t	queue_mutex;
# endif
}	t_rtapp;

/*--------------------------------------------------------------------------*/
/*--------------------------------APP_STEPS---------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Initializes the miniRT application from command line arguments.
 * @param argc The number of command line arguments.
 * @param argv The array of command line argument strings, where argv[1]
 * is the path to the scene file.
 * @param app The T_RTAPP instance to initialize.
 * @return RT_SUCCESS if the application was initialized correctly,
 * RT_FAILURE if argc is not 2, the file cannot be read, or any scene
 * element fails to parse or initialize.
 * @note Expects exactly one argument — the path to a .rt scene file.
 * @note BONUS: Initializes the log file descriptor after scene parsing,
 * restoring orig_outfd and orig_errfd to -1 as uninitialized sentinels.
 */
int	rtapp_init(int argc, char **argv, t_rtapp *app);

/**
 * Cleans up all application resources and restores file descriptors.
 * @param app The T_RTAPP instance to clean up.
 * @return Always returns RT_SUCCESS.
 * @note Clears the object list using rtfree before restoring stdout and
 * stderr to their original file descriptors if they were redirected.
 * @note BONUS: Restores the original stdout and stderr file descriptors
 * saved in app->logfd if they were redirected during logging. Logs an
 * error if either dup2 restoration fails but continues cleanup regardless.
 */
# if BONUS
int	rtapp_kill(t_rtapp *app);
# else
int	rtapp_kill(t_rtapp *app, t_rterr errcode);
# endif

int	rtapp_render(t_rtapp *app);

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif