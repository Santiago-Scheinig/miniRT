/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:38:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/23 19:55:51 by aramos-r         ###   ########.fr       */
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
#  include "rtapp_bonus.h"
# endif

# ifndef DEV
#  define DEV 0
# endif

/*--------------------------------------------------------------------------*/
/*--------------------------------STRUCTURES--------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Represents the full state of the miniRT application.
 * @note objects and lights are NULL until parsed from the scene file.
 * camera.get_pixel_ray being NULL indicates the camera is uninitialized.
 * ambient.ratio being -1 indicates the ambient light is uninitialized.
 */
typedef struct s_rtapp
{
	uint32_t		*img; // Render buffer for img, allocated after parsing.
	t_list			*objects;	// Linked list of T_OBJECT scene elements.
	t_list			*lights;	// Linked list of T_ELEM_LIGHT_P point lights.
	t_elem_camera	camera;		// Unique camera instance for the scene.
	t_elem_light_a	ambient;	// Unique ambient light instance for the scene.
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
int	rtapp_kill(t_rtapp *app, t_rterr errcode);

int	rtapp_render(t_rtapp *app);

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif