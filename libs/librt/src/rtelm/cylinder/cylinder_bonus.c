/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 19:41:18 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 17:35:33 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "../.include/rtelm_private.h"

static t_vector	cy_calc_tangent(t_vector local_point)
{
	t_vector	t;

	t = vector_new(-local_point.z, 0.0, local_point.x);
	return (vector_normalize(t));
}

static t_uv	cy_calc_uv_map(t_vector local_point)
{
	t_uv	uv;

	uv.u = atan2(local_point.z, local_point.x) / (2.0 * M_PI) + 0.5;
	uv.v = (local_point.y + 1.0) / 2.0;
	return (uv);
}

static double	cy_calc_intersection(t_ray local_ray)
{
	double	sides_intersection;
	double	ends_intersection;

	sides_intersection = cy_calc_sides_intersection(local_ray);
	ends_intersection = cy_calc_ends_intersection(local_ray);
	if (sides_intersection < EPSILON && ends_intersection < EPSILON)
		return (INFINITY);
	else if (sides_intersection > EPSILON && ends_intersection > EPSILON)
		return (fmin(sides_intersection, ends_intersection));
	else if (sides_intersection > EPSILON)
		return (sides_intersection);
	else if (ends_intersection > EPSILON)
		return (ends_intersection);
	else
		return (INFINITY);
}

/**
 * Computes the object space normal of a cylinder at a given surface point.
 * @param local_point The point on the cylinder surface in local object space.
 * @return The outward facing normal vector at LOCAL_POINT. Returns (0,1,0)
 * for the top cap, (0,-1,0) for the bottom cap, and a radial normal for
 * the side surface.
 * @note Cap detection uses EPSILON tolerance to handle floating point
 * imprecision at the cap boundaries.
 */
static t_vector	cy_calc_normal(t_vector local_point)
{
	if (local_point.y >= 1.0 - EPSILON)
		return (vector_new(0.0, 1.0, 0.0));
	if (local_point.y <= -1.0 + EPSILON)
		return (vector_new(0.0, -1.0, 0.0));
	return (vector_new(local_point.x, 0.0, local_point.z));
}

int	build_cy(char **arr, t_object *obj)
{
	t_elem_quadric	*data;
	t_vector		position;
	t_vector		normal;
	t_vector		scale;

	position = build_vector(arr[1]);
	normal = build_vector(arr[2]);
	if (!normal.x && !normal.y && !normal.z)
		return (1);
	data = ft_calloc(1, sizeof(t_elem_quadric));
	if (!data)
		return (1);
	data->radius = ft_atod(arr[3]) / 2.0;
	data->height = ft_atod(arr[4]);
	obj->material.color = build_color(arr[5]);
	build_add_att(obj, &arr[6]);
	scale = vector_new(data->radius, data->height / 2.0, data->radius);
	build_matrixes(obj, position, normal, scale);
	obj->c_intersection = &cy_calc_intersection;
	obj->c_normal = &cy_calc_normal;
	obj->c_tangent = &cy_calc_tangent;
	obj->c_uv_map = &cy_calc_uv_map;
	obj->data = data;
	return (0);
}
