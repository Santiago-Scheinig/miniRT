/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:21:46 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/17 15:41:02 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "rtelm_private.h"

/**
 * Computes the object space normal of a cylinder at a given surface point.
 * @param local_point The point on the cylinder surface in local object space.
 * @return The outward facing normal vector at LOCAL_POINT. Returns (0,1,0)
 * for the top cap, (0,-1,0) for the bottom cap, and a radial normal for
 * the side surface.
 * @note Cap detection uses EPSILON tolerance to handle floating point
 * imprecision at the cap boundaries.
 */
static t_vector	cy_normal(t_vector local_point)
{
	if (local_point.y >= 1.0 - EPSILON)
		return (vector_new(0.0, 1.0, 0.0));
	if (local_point.y <= -1.0 + EPSILON)
		return (vector_new(0.0, -1.0, 0.0));
	return (vector_new(local_point.x, 0.0, local_point.z));
}

int	build_cy(char **str, t_object *obj)
{
	t_elem_quadric	*data;
	t_vector		position;
	t_vector		normal;
	t_vector		scale;

	position = build_vector(str[1]);
	normal = build_vector(str[2]);
	if (!normal.x && !normal.y && !normal.z)
		return (1);
	data = ft_calloc(1, sizeof(t_elem_quadric));
	if (!data)
		return (1);
	data->radius = ft_atod(str[3]) / 2.0;
	data->height = ft_atod(str[4]);
	obj->material.color = build_color(str[5]);
	obj->data = data;
	obj->c_intersection = &cy_intersection;
	obj->c_normal = &cy_normal;
	scale.x = data->radius;
	scale.y = data->height / 2.0;
	scale.z = data->radius;
	build_matrixes(obj, position, normal, scale);
	return (0);
}
