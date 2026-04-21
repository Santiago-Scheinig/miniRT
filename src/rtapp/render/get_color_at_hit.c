/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_at_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:33:41 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/21 18:01:50 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_render.h"

t_vector	get_color_at_hit(
	t_hit hit,
	t_object *objs,
	t_elem_light_p *lights,
	t_elem_light_a *alight
)
{
	t_vector	res;
	t_vector	tmp_color;

	res = vector_new(0, 0, 0);
	tmp_color = hit.obj->material.color;
}
