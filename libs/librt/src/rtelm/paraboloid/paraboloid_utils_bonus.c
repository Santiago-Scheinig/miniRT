/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_cat_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 19:56:57 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 17:28:33 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "../.include/rtelm_private.h"

t_roots	pb_calc_roots(t_ray local_ray)
{
	double	a;
	double	b;
	double	c;

	a = (local_ray.direction.x * local_ray.direction.x)
		+ (local_ray.direction.z * local_ray.direction.z);
	b = 2.0 * (local_ray.origin.x * local_ray.direction.x
			+ local_ray.origin.z * local_ray.direction.z)
		- local_ray.direction.y;
	c = (local_ray.origin.x * local_ray.origin.x)
		+ (local_ray.origin.z * local_ray.origin.z)
		- local_ray.origin.y;
	return (solve_quadratic(a, b, c));
}

double	pb_calc_cap_dist(t_ray local_ray)
{
	double		t;
	t_vector	intersection_point;

	if (fabs(local_ray.direction.y) < EPSILON)
		return (INFINITY);
	t = (1.0 - local_ray.origin.y) / local_ray.direction.y;
	if (t < EPSILON)
		return (INFINITY);
	intersection_point = ray_point_at(local_ray, t);
	if ((intersection_point.x * intersection_point.x)
		+ (intersection_point.z * intersection_point.z) <= 1.0)
		return (t);
	return (INFINITY);
}

t_vector	pb_calc_tangent(t_vector local_point)
{
	t_vector	t;

	t = vector_new(-local_point.z, 0.0, local_point.x);
	return (vector_normalize(t));
}

t_uv	pb_calc_uv_map(t_vector local_point)
{
	t_uv	uv;

	uv.u = atan2(local_point.z, local_point.x) / (2.0 * M_PI) + 0.5;
	uv.v = local_point.y;
	return (uv);
}
