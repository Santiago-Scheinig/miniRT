/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:27:31 by aramos-r          #+#    #+#             */
/*   Updated: 2026/06/15 16:27:33 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "../.include/rtelm_private.h"

static double	pb_calc_sides_intersection(t_ray local_ray)
{
	t_roots		roots;
	t_vector	p1;
	t_vector	p2;
	double		valid_t;

	roots = pb_calc_roots(local_ray);
	if (!roots.has_solutions)
		return (INFINITY);
	valid_t = INFINITY;
	if (roots.sol1 > EPSILON)
	{
		p1 = ray_point_at(local_ray, roots.sol1);
		if (p1.y >= 0.0 && p1.y <= 1.0)
			valid_t = roots.sol1;
	}
	if (roots.sol2 > EPSILON && roots.sol2 < valid_t)
	{
		p2 = ray_point_at(local_ray, roots.sol2);
		if (p2.y >= 0.0 && p2.y <= 1.0)
			valid_t = roots.sol2;
	}
	return (valid_t);
}

static double	pb_calc_intersection(t_ray local_ray)
{
	double	sides_t;
	double	cap_t;

	sides_t = pb_calc_sides_intersection(local_ray);
	cap_t = pb_calc_cap_dist(local_ray);
	if (sides_t < EPSILON && cap_t < EPSILON)
		return (INFINITY);
	if (sides_t > EPSILON && cap_t > EPSILON)
		return (fmin(sides_t, cap_t));
	if (sides_t > EPSILON)
		return (sides_t);
	return (cap_t);
}

static t_vector	pb_calc_normal(t_vector local_point)
{
	t_vector	normal;

	if (local_point.y >= 1.0 - EPSILON)
		return (vector_new(0.0, 1.0, 0.0));
	normal = vector_new(2.0 * local_point.x, -1.0, 2.0 * local_point.z);
	return (vector_normalize(normal));
}

int	build_pb(char **str, t_object *obj)
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
	scale = vector_new(data->radius, data->height, data->radius);
	build_matrixes(obj, position, normal, scale);
	obj->c_intersection = &pb_calc_intersection;
	obj->c_normal = &pb_calc_normal;
	obj->c_tangent = &pb_calc_tangent;
	obj->c_uv_map = &pb_calc_uv_map;
	obj->data = data;
	return (0);
}
