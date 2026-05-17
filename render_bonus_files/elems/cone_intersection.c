/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 17:25:02 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/17 17:25:39 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Computes the intersection distance of a ray with the cone's single base cap.
 * @param local_ray The ray in the cone's local object space.
 * @return The distance T to the cap intersection, or INFINITY if the ray
 * misses or hits behind the origin.
 * @note The canonical cone has a single cap at Y = 1.0 with a radius of 1.0.
 */
static double	get_cone_cap_dist(t_ray local_ray)
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

/**
 * Computes the quadratic coefficients for a ray-cone side intersection.
 * @param local_ray The ray in the cone's local object space.
 * @return A T_ROOTS containing the solutions to the quadratic equation
 * derived from the canonical cone equation x² + z² - y² = 0.
 */
static t_roots	get_cone_roots(t_ray local_ray)
{
	double	a;
	double	b;
	double	c;

	a = (local_ray.direction.x * local_ray.direction.x)
		- (local_ray.direction.y * local_ray.direction.y)
		+ (local_ray.direction.z * local_ray.direction.z);
	b = 2 * (local_ray.origin.x * local_ray.direction.x
			- local_ray.origin.y * local_ray.direction.y
			+ local_ray.origin.z * local_ray.direction.z);
	c = (local_ray.origin.x * local_ray.origin.x)
		- (local_ray.origin.y * local_ray.origin.y)
		+ (local_ray.origin.z * local_ray.origin.z);
	return (solve_quadratic(a, b, c));
}

/**
 * Computes the closest valid intersection distance with the cone's sides.
 * @param local_ray The ray in the cone's local object space.
 * @return The smallest valid intersection distance T, or INFINITY.
 * @note A valid intersection must have an intersection point where 
 * 0.0 <= Y <= 1.0 to avoid rendering the infinite double cone.
 * @note Now the cone is finite with a single cap at Y=1.0,
 * if in the future we want to make it infinite we can just remove the
 * y range check and return the smallest positive root.
 */
static double	get_cone_sides_intersection(t_ray local_ray)
{
	t_roots		roots;
	t_vector	p1;
	t_vector	p2;
	double		valid_t;

	roots = get_cone_roots(local_ray);
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

double	cn_intersection(t_ray local_ray)
{
	double	sides_t;
	double	cap_t;

	sides_t = get_cone_sides_intersection(local_ray);
	cap_t = get_cone_cap_dist(local_ray);
	if (sides_t < cap_t)
		return (sides_t);
	return (cap_t);
}