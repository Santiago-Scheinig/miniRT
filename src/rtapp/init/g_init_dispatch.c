/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_init_dispatch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:11:22 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/20 18:27:03 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"
#include "rtapp_parser.h"

/**
 * Dispatch table mapping object specifiers to their builder functions.
 * @note Each entry pairs a specifier with its parse, build and info
 * functions. The info field is NULL in base mode and set in dev builds.
 * Terminated by a NULL sentinel entry. Replace this file with the bonus
 * version to add new geometric object types without modifying any logic.
 */
const t_obj_dispatch	g_obj_dispatch[] = {
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
const t_dispatch		g_dispatch[] = {
{"pl", &init_object},
{"cy", &init_object},
{"sp", &init_object},
{"C", &init_camera},
{"L", &init_light_p},
{"A", &init_light_a},
{NULL, NULL}
};