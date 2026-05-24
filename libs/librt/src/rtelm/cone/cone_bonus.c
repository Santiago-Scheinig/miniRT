/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:19:21 by aramos-r          #+#    #+#             */
/*   Updated: 2026/05/24 18:49:50 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "../.include/rtelm_private.h"

static double	cn_calc_intersection(t_ray local_ray)
{
	double	sides_t;
	double	cap_t;

	sides_t = cn_calc_sides_intersection(local_ray);
	cap_t = cn_calc_cap_dist(local_ray);
	if (sides_t < cap_t)
		return (sides_t);
	return (cap_t);
}

static t_vector	cn_calc_tangent(t_vector local_point)
{
	t_vector	t;

	t = vector_new(-local_point.z, 0.0, local_point.x);
	return (vector_normalize(t));
}

static t_uv	cn_calc_uv_map(t_vector local_point)
{
	t_uv	uv;

	uv.u = atan2(local_point.z, local_point.x) / (2.0 * M_PI) + 0.5;
	uv.v = local_point.y;
	return (uv);
}

static t_vector	cn_calc_normal(t_vector local_point)
{
	t_vector	normal;

	if (local_point.y >= 1.0 - EPSILON)
		return (vector_new(0.0, 1.0, 0.0));
	normal = vector_new(local_point.x, -local_point.y, local_point.z);
	return (vector_normalize(normal));
}

int	build_cn(char **arr, t_object *obj)
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
	scale = vector_new(data->radius, data->height, data->radius);
	build_matrixes(obj, position, normal, scale);
	obj->c_intersection = &cn_calc_intersection;
	obj->c_normal = &cn_calc_normal;
	obj->c_uv_map = &cn_calc_uv_map;
	obj->c_tangent = &cn_calc_tangent;
	obj->data = data;
	return (0);
}
