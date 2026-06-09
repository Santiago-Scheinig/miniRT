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

#ifndef G_INIT_DISPATCH_BONUS_H
# define G_INIT_DISPATCH_BONUS_H

# include "rtapp.h"
# include "rtapp_init.h"
# include "rtapp_parser.h"

/*--------------------------------------------------------------------------*/
/*--------------------------------STRUCTURES--------------------------------*/
/*--------------------------------------------------------------------------*/

typedef struct s_object_build
{
	const char *const	*g_msgs;
	int					(*parse)(char **, int,
			const char *const *);
	int					(*build)(char **, t_object *);
	int					(*info)(t_object *);
}	t_object_build;

typedef struct s_dispatch
{
	const char	*specifier;
	int			(*initializer)(char **, int, t_rtapp *);
}	t_dispatch;

typedef struct s_obj_dispatch
{
	const char		*specifier;
	t_object_build	builder;
}	t_obj_dispatch;

/*--------------------------------------------------------------------------*/
/*----------------------------------GLOBAL----------------------------------*/
/*--------------------------------------------------------------------------*/

static const t_obj_dispatch	g_obj_dispatch[] = {
{"pl", {g_pl_msgs, &parse_pl, &build_pl, NULL}},
{"sp", {g_sp_msgs, &parse_sp, &build_sp, NULL}},
{"cy", {g_cy_msgs, &parse_quadric, &build_cy, NULL}},
{"cn", {g_cn_msgs, &parse_quadric, &build_cn, NULL}},
{"pb", {g_pb_msgs, &parse_quadric, &build_pb, NULL}},
{"hb", {g_hb_msgs, &parse_quadric, &build_hb, NULL}},
{NULL, {NULL, NULL, NULL, NULL}}
};

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