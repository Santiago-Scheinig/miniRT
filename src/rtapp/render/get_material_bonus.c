/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_material_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:00:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/29 00:00:00 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_render_bonus.h"

t_vector	get_checker_color(t_uv uv)
{
	int	iu;
	int	iv;

	iu = (int)floor(uv.u * CHECKER_SCALE);
	iv = (int)floor(uv.v * CHECKER_SCALE);
	if ((iu + iv) % 2 == 0)
		return (vector_new(1.0, 1.0, 1.0));
	return (vector_new(0.0, 0.0, 0.0));
}

t_vector	get_material_color(t_object *obj, t_vector local_point)
{
	t_uv	uv;

	if (obj->material.is_checker && obj->c_uv_map)
	{
		uv = obj->c_uv_map(local_point);
		return (get_checker_color(uv));
	}
	return (obj->material.color);
}

t_vector	get_lighting_normal(t_hit hit, t_vector local_point)
{
	if (hit.obj->material.map.img && hit.obj->c_tangent)
		return (get_perturbed_normal(hit, local_point));
	return (hit.surf_normal);
}
