/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:54:39 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/11 20:43:03 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

static double	get_cap_dist(t_ray local_ray, double height)
{
	double		t;
	t_vector	intersection_point;

	if (fabs(local_ray.direction.y) < EPSILON)
		return (INFINITY);
	t = (height - local_ray.origin.y) / local_ray.direction.y;
	if (t < EPSILON)
		return (INFINITY);
	intersection_point = ray_point_at(local_ray, t);
	if ((intersection_point.x * intersection_point.x)
		+ (intersection_point.z * intersection_point.z) <= 1.0)
		return (t);
	else
		return (INFINITY);
}

static double	get_ends_intersection(t_ray local_ray)
{
	double			top_intersection;
	double			bottom_intersection;

	top_intersection = get_cap_dist(local_ray, 1.0);
	bottom_intersection = get_cap_dist(local_ray, -1.0);
	if (top_intersection > EPSILON && bottom_intersection > EPSILON)
		return (fmin(top_intersection, bottom_intersection));
	else if (top_intersection > EPSILON)
		return (top_intersection);
	else if (bottom_intersection > EPSILON)
		return (bottom_intersection);
	else
		return (INFINITY);
}

static t_roots	get_roots(t_ray local_ray)
{
	double	a;
	double	b;
	double	c;
	t_roots	roots;

	a = (local_ray.direction.x * local_ray.direction.x)
		+ (local_ray.direction.z * local_ray.direction.z);
	b = 2 * (local_ray.origin.x * local_ray.direction.x
			+ local_ray.origin.z * local_ray.direction.z);
	c = (local_ray.origin.x * local_ray.origin.x)
		+ (local_ray.origin.z * local_ray.origin.z) - 1.0;
	roots = solve_quadratic(a, b, c);
	return (roots);
}

static double	get_sides_intersection(t_ray local_ray)
{
	t_roots			roots;
	t_vector		intersection_point;

	roots = get_roots(local_ray);
	if (!roots.has_solutions)
		return (INFINITY);
	intersection_point = ray_point_at(local_ray, roots.sol1);
	if (roots.sol1 > EPSILON && intersection_point.y > -1.0
		&& intersection_point.y < 1.0)
		return (roots.sol1);
	intersection_point = ray_point_at(local_ray, roots.sol2);
	if (roots.sol2 > EPSILON && intersection_point.y > -1.0
		&& intersection_point.y < 1.0)
		return (roots.sol2);
	return (INFINITY);
}

double	cylinder_intersection(t_ray local_ray)
{
	double	sides_intersection;
	double	ends_intersection;

	sides_intersection = get_sides_intersection(local_ray);
	ends_intersection = get_ends_intersection(local_ray);
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