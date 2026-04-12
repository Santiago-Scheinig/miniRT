/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_init_dispatch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:11:22 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 18:17:50 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"
#include "rtapp_parser.h"

const t_obj_dispatch	g_obj_dispatch[] = {
{"pl", {&parse_pl, &build_pl, NULL}},
{"cy", {&parse_cy, &build_cy, NULL}},
{"sp", {&parse_sp, &build_sp, NULL}},
{NULL, {NULL, NULL, NULL}}
};

const t_dispatch		g_dispatch[] = {
{"pl", &init_object},
{"cy", &init_object},
{"sp", &init_object},
{"C", &init_camera},
{"L", &init_light_p},
{"A", &init_light_a},
{NULL, NULL}
};