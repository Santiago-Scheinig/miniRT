/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_init_dispatch_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:11:22 by sscheini          #+#    #+#             */
/*   Updated: 2026/06/15 16:07:11 by aramos-r         ###   ########.fr       */
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
	int					(*parse)(char **arr, int i,
			const char *const *msg);
	int					(*build)(char **arr, t_object *obj);
	int					(*info)(t_object *obj);
}	t_object_build;

typedef struct s_dispatch
{
	const char	*specifier;
	int			(*initializer)(char **arr, int i, t_rtapp *app);
}	t_dispatch;

typedef struct s_obj_dispatch
{
	const char		*specifier;
	t_object_build	builder;
}	t_obj_dispatch;

/*--------------------------------------------------------------------------*/
/*----------------------------------GLOBAL----------------------------------*/
/*--------------------------------------------------------------------------*/

static const t_obj_dispatch	g_obj_dispatch[] =
{
	{"pl", {g_pl_msgs, &parse_pl, &build_pl, NULL}},
	{"sp", {g_sp_msgs, &parse_sp, &build_sp, NULL}},
	{"cy", {g_cy_msgs, &parse_quadric, &build_cy, NULL}},
	{"cn", {g_cn_msgs, &parse_quadric, &build_cn, NULL}},
	{"pb", {g_pb_msgs, &parse_quadric, &build_pb, NULL}},
	{"hb", {g_hb_msgs, &parse_quadric, &build_hb, NULL}},
	{NULL, {NULL, NULL, NULL, NULL}}
};

static const t_dispatch		g_dispatch[] =
{
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