/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_init_dispatch.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:11:22 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/25 17:32:51 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_INIT_DISPATCH_H
# define G_INIT_DISPATCH_H

# include "rtapp_init.h"
# include "rtapp_parser.h"

# if BONUS
#  include "g_init_dispatch_bonus.h"
# else

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
 * @note Each entry pairs a specifier with its parse, build and info
 * functions. The info field is NULL in base mode and set in dev builds.
 * Terminated by a NULL sentinel entry. Replace this file with the bonus
 * version to add new geometric object types without modifying any logic.
 */
static const t_obj_dispatch	g_obj_dispatch[] = {
{"pl", {&parse_pl, &build_pl, NULL}},
{"cy", {&parse_cy, &build_cy, NULL}},
{"sp", {&parse_sp, &build_sp, NULL}},
{NULL, {NULL, NULL, NULL}}
};

/**
 * Dispatch table mapping all scene element specifiers to their
 * initializer functions.
 * @note Geometric objects share init_object as their initializer, which
 * looks up the correct builder from g_obj_dispatch internally. Non-geometric
 * elements have their own dedicated initializer. Terminated by a NULL
 * sentinel entry. Replace this file with the bonus version to support
 * additional scene element types without modifying any logic.
 */
static const t_dispatch		g_dispatch[] = {
{"pl", &init_object},
{"cy", &init_object},
{"sp", &init_object},
{"C", &init_camera},
{"L", &init_light_p},
{"A", &init_light_a},
{NULL, NULL}
};

# endif

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif
