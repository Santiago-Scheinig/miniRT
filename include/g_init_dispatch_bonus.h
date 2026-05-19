/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_init_dispatch_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:11:22 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/19 20:24:06 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_INIT_DISPATCH_BONUSH
# define G_INIT_DISPATCH_BONUSH

# include "rtapp.h"
# include "rtapp_init.h"
# include "rtapp_parser.h"

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
	const char *const	*g_msgs;
	int					(*parse)(char **arr, int i, const char *const *g_msgs);
	int					(*build)(char **arr, t_object *obj); // Allocates and fills the object.
	int					(*info)(t_object *obj); // Prints debug info, NULL in release.
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
	const char			*specifier; // Scene file object identifier.
	t_object_build		builder;	// Parse, build and info function group.
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
{"pl", {g_pl_msgs, &parse_pl, &build_pl, NULL}},
{"sp", {g_sp_msgs, &parse_sp, &build_sp, NULL}},
{"cy", {g_cy_msgs, &parse_quadric, &build_cy, NULL}},
{"cn", {g_cn_msgs, &parse_quadric, &build_cn, NULL}},
{"pb", {g_pb_msgs, &parse_quadric, &build_pb, NULL}},
{"hb", {g_hb_msgs, &parse_quadric, &build_hb, NULL}},
{NULL, {NULL, NULL, NULL, NULL}}
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
{"hb", &init_object},
{"cn", &init_object},
{"pb", &init_object},
{"C", &init_camera},
{"L", &init_light_p},
{"A", &init_light_a},
{NULL, NULL}
};

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif
