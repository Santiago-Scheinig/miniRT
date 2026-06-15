/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:27:26 by aramos-r          #+#    #+#             */
/*   Updated: 2026/06/15 16:27:27 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "../.include/rtelm_private.h"

static double	hb_calc_sides_intersection(t_ray local_ray)
{
	t_roots		roots;
	t_vector	p1;
	t_vector	p2;
	double		valid_t;

	roots = hb_get_roots(local_ray);
	if (!roots.has_solutions)
		return (INFINITY);
	valid_t = INFINITY;
	if (roots.sol1 > EPSILON)
	{
		p1 = ray_point_at(local_ray, roots.sol1);
		if (p1.y >= -1.0 && p1.y <= 1.0)
			valid_t = roots.sol1;
	}
	if (roots.sol2 > EPSILON && roots.sol2 < valid_t)
	{
		p2 = ray_point_at(local_ray, roots.sol2);
		if (p2.y >= -1.0 && p2.y <= 1.0)
			valid_t = roots.sol2;
	}
	return (valid_t);
}

static double	hb_calc_intersection(t_ray local_ray)
{
	double	sides_t;
	double	ends_t;

	sides_t = hb_calc_sides_intersection(local_ray);
	ends_t = hb_calc_ends_intersection(local_ray);
	if (sides_t < EPSILON && ends_t < EPSILON)
		return (INFINITY);
	if (sides_t > EPSILON && ends_t > EPSILON)
		return (fmin(sides_t, ends_t));
	if (sides_t > EPSILON)
		return (sides_t);
	if (ends_t > EPSILON)
		return (ends_t);
	return (INFINITY);
}

static t_vector	hb_calc_normal(t_vector local_point)
{
	if (local_point.y >= 1.0 - EPSILON)
		return (vector_new(0.0, 1.0, 0.0));
	if (local_point.y <= -1.0 + EPSILON)
		return (vector_new(0.0, -1.0, 0.0));
	return (vector_normalize(vector_new(
				2.0 * local_point.x,
				-2.0 * local_point.y,
				2.0 * local_point.z)));
}

int	build_hb(char **str, t_object *obj)
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
	build_add_att(obj, &str[6]);
	scale = vector_new(data->radius, data->height / 2.0, data->radius);
	build_matrixes(obj, position, normal, scale);
	obj->c_intersection = &hb_calc_intersection;
	obj->c_normal = &hb_calc_normal;
	obj->c_uv_map = &hb_calc_uv_map;
	obj->c_tangent = &hb_calc_tangent;
	obj->data = data;
	return (0);
}
