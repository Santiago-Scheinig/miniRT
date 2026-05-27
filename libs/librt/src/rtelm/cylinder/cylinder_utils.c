/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:54:39 by aramos-r          #+#    #+#             */
/*   Updated: 2026/05/24 17:28:50 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "../.include/rtelm_private.h"

/**
 * Computes the intersection distance of a ray with a cylinder cap.
 * @param local_ray The ray in the cylinder's local object space.
 * @param height The Y coordinate of the cap, either 1.0 (top) or -1.0
 * (bottom) in local space.
 * @return The distance T to the cap intersection, or INFINITY if the ray
 * is parallel to the cap, hits behind the origin, or misses the cap radius.
 * @note The canonical cylinder has radius 1 and height from -1 to 1.
 */
double	cy_calc_cap_dist(t_ray local_ray, double height)
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

/**
 * Computes the closest intersection distance of a ray with either cap.
 * @param local_ray The ray in the cylinder's local object space.
 * @return The smallest valid intersection distance T with either the top
 * or bottom cap, or INFINITY if neither cap is hit.
 */
double	cy_calc_ends_intersection(t_ray local_ray)
{
	double			top_intersection;
	double			bottom_intersection;

	top_intersection = cy_calc_cap_dist(local_ray, 1.0);
	bottom_intersection = cy_calc_cap_dist(local_ray, -1.0);
	if (top_intersection > EPSILON && bottom_intersection > EPSILON)
		return (fmin(top_intersection, bottom_intersection));
	else if (top_intersection > EPSILON)
		return (top_intersection);
	else if (bottom_intersection > EPSILON)
		return (bottom_intersection);
	else
		return (INFINITY);
}

/**
 * Computes the quadratic coefficients for a ray-cylinder side intersection.
 * @param local_ray The ray in the cylinder's local object space.
 * @return A T_ROOTS containing the solutions to the quadratic equation
 * derived from the ray and the infinite cylinder equation x² + z² = 1.
 * @note Only the X and Z components are used since the cylinder is
 * infinite along the Y axis in local space.
 */
t_roots	cy_calc_roots(t_ray local_ray)
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

/**
 * Computes the closest intersection distance of a ray with the cylinder sides.
 * @param local_ray The ray in the cylinder's local object space.
 * @return The smallest valid intersection distance T with the cylinder
 * side surface, or INFINITY if no valid intersection exists.
 * @note A valid intersection must be in front of the ray origin (T > EPSILON)
 * and within the cylinder's height range (-1.0 to 1.0 in local space).
 */
double	cy_calc_sides_intersection(t_ray local_ray)
{
	t_roots			roots;
	t_vector		intersection_point;

	roots = cy_calc_roots(local_ray);
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
