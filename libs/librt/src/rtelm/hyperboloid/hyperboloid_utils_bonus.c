/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 19:55:27 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 17:28:45 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "../.include/rtelm_private.h"

t_roots	hb_get_roots(t_ray local_ray)
{
	double	a;
	double	b;
	double	c;

	a = (local_ray.direction.x * local_ray.direction.x)
		- (local_ray.direction.y * local_ray.direction.y)
		+ (local_ray.direction.z * local_ray.direction.z);
	b = 2.0 * (local_ray.origin.x * local_ray.direction.x
			- local_ray.origin.y * local_ray.direction.y
			+ local_ray.origin.z * local_ray.direction.z);
	c = (local_ray.origin.x * local_ray.origin.x)
		- (local_ray.origin.y * local_ray.origin.y)
		+ (local_ray.origin.z * local_ray.origin.z) - 1.0;
	return (solve_quadratic(a, b, c));
}

double	hb_calc_cap_dist(t_ray local_ray, double height)
{
	double		t;
	double		radius_sq;
	t_vector	intersection_point;

	if (fabs(local_ray.direction.y) < EPSILON)
		return (INFINITY);
	t = (height - local_ray.origin.y) / local_ray.direction.y;
	if (t < EPSILON)
		return (INFINITY);
	intersection_point = ray_point_at(local_ray, t);
	radius_sq = 1.0 + height * height;
	if ((intersection_point.x * intersection_point.x)
		+ (intersection_point.z * intersection_point.z) <= radius_sq)
		return (t);
	return (INFINITY);
}

double	hb_calc_ends_intersection(t_ray local_ray)
{
	double	top;
	double	bottom;

	top = hb_calc_cap_dist(local_ray, 1.0);
	bottom = hb_calc_cap_dist(local_ray, -1.0);
	if (top > EPSILON && bottom > EPSILON)
		return (fmin(top, bottom));
	if (top > EPSILON)
		return (top);
	if (bottom > EPSILON)
		return (bottom);
	return (INFINITY);
}