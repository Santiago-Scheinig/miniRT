/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_init.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:10:37 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/23 20:00:14 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_INIT_H
# define RTAPP_INIT_H

# include "rtapp.h"

/*--------------------------------------------------------------------------*/
/*--------------------------------STRUCTURES--------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Groups the parse, build and info function pointers for a geometric object.
 * @note parse validates the raw string arguments, build allocates and fills
 * the object, and info prints debug data in dev builds. info is NULL in
 * release builds. Used as the builder field in T_OBJ_DISPATCH entries.
 */
typedef struct s_object_build
{
	int	(*parse)(char **arr, int i); // Validates raw string arguments.
	int	(*build)(char **arr, t_object *obj); // Allocates and fills the object.
	int	(*info)(t_object *obj); // Prints debug info, NULL in release.
}	t_object_build;

/**
 * Maps a scene element specifier to its initializer function.
 * @note Used in g_dispatch to route parsed lines to the correct init
 * function. Terminated by a NULL sentinel entry.
 */
typedef struct s_dispatch
{
	const char	*specifier;	// Scene file element identifier.
	int			(*initializer)(char **, int, t_rtapp *); // Elem init function.
}	t_dispatch;

/**
 * Maps a geometric object specifier to its T_OBJECT_BUILD function group.
 * @note Used in g_obj_dispatch to route init_object to the correct parse,
 * build and info functions for each geometric type. Terminated by a NULL
 * sentinel entry.
 */
typedef struct s_obj_dispatch
{
	const char		*specifier; // Scene file object identifier.
	t_object_build	builder;	// Parse, build and info function group.
}	t_obj_dispatch;

/*--------------------------------------------------------------------------*/
/*----------------------------------GLOBAL----------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Dispatch table mapping object specifiers to their builder functions.
 * @note Replace the definition in g_init_dispatch.c with the bonus
 * version to add new geometric object types without modifying any logic.
 */
extern const t_obj_dispatch	g_obj_dispatch[];

/**
 * Dispatch table mapping all scene element specifiers to their
 * initializer functions.
 * @note Replace the definition in g_init_dispatch.c with the bonus
 * version to support additional scene element types without modifying
 * any logic.
 */
extern const t_dispatch		g_dispatch[];

/*--------------------------------------------------------------------------*/
/*------------------------------INITIALIZATION------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Opens and reads a .rt scene file into a linked list of lines.
 * @param file The path to the scene file to open and read.
 * @return A T_LIST of strings, one node per line, or NULL if the file
 * extension is invalid, the file cannot be opened, reading fails, or
 * the file is empty.
 * @note The returned list must be freed by the caller. Each node's
 * content is a heap-allocated string freed with free.
 */
t_list		*init_file(char *file);

/**
 * Parses and initializes all scene elements from a linked list of lines.
 * @param lines The T_LIST of raw scene file lines to process.
 * @param file The scene file path, used for error logging.
 * @param app The T_RTAPP instance to initialize all elements into.
 * @return RT_SUCCESS if all lines parsed successfully and both ambient
 * light and camera are defined, RT_FAILURE if any line fails to parse,
 * or if the scene has no ambient light or no camera defined.
 * @note Sets ambient.ratio to -1 before parsing as the uninitialized
 * sentinel. Frees the lines list before returning in all cases.
 */
int			init_file_contents(t_list *lines, char *file, t_rtapp *app);

/**
 * Parses and initializes the scene's camera into the app.
 * @param argv The array of strings containing the camera parameters.
 * @param i The line number in the scene file, used for error logging.
 * @param app The T_RTAPP instance to initialize the camera into.
 * @return RT_SUCCESS on success, RT_FAILURE if the camera was already
 * defined, parsing fails, or the normal vector is zero.
 * @note Uses camera.get_pixel_ray == NULL as the uninitialized sentinel.
 */
int			init_camera(char **argv, int i, t_rtapp *app);

/**
 * Parses and initializes the scene's ambient light into the app.
 * @param argv The array of strings containing the ambient light parameters.
 * @param i The line number in the scene file, used for error logging.
 * @param app The T_RTAPP instance to initialize the ambient light into.
 * @return RT_SUCCESS on success, RT_FAILURE if the ambient light was
 * already defined or if parsing fails.
 * @note Uses ambient.ratio == -1 as the uninitialized sentinel.
 */
int			init_light_a(char **argv, int i, t_rtapp *app);

/**
 * Parses and initializes a point light and adds it to the app light list.
 * @param argv The array of strings containing the point light parameters.
 * @param i The line number in the scene file, used for error logging.
 * @param app The T_RTAPP instance to add the point light into.
 * @return RT_SUCCESS on success, RT_FAILURE if a light was already defined,
 * parsing fails, or allocation of the light or list node fails.
 * @note Only one point light is supported in base mode. The bonus version
 * removes this restriction.
 */
int			init_light_p(char **argv, int i, t_rtapp *app);

/**
 * Looks up the builder for a geometric object and delegates to build_and_add.
 * @param arr The array of strings where arr[0] is the object specifier
 * and the remaining entries are its parameters.
 * @param i The line number in the scene file, used for error logging.
 * @param app The T_RTAPP instance to add the object into.
 * @return RT_SUCCESS if the object was built and added successfully,
 * RT_FAILURE if the specifier is not found or build_and_add fails.
 * @note Dispatches through g_obj_dispatch using exact specifier matching.
 * Replace g_obj_dispatch with the bonus version to support extra types.
 */
int			init_object(char **argv, int i, t_rtapp *app);

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif