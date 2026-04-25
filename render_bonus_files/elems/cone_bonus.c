/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:19:21 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/25 18:17:08 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_bonus.h"

/**
∗ identifier: cn
∗ x, y, z coordinates of the center of the cone: 50.0,0.0,20.6
∗ 3D normalized vector of axis of cone, in the range [-1,1] for each x, y, z axis: 0.0,0.0,1.0
∗ the cone diameter: 14.2
∗ the cone height: 21.42
∗ R, G, B colors in the range [0,255]: 10, 0, 255
* The bonus extra parameters (reflection and checkers)
* Example: cn 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
*/

t_mat4	cn_inv_mat4(t_object *obj, t_vector pos, t_vector normal)
{
	t_elem_cone		*cone;
	t_mat4			inv;
	t_mat4			trans;
	t_mat4			rot;
	t_mat4			scale;

	cone = (t_elem_cone *) obj->data;
	trans = mat4_translation(pos.x, pos.y, pos.z);
	scale = mat4_scale(cone->diam / 2.0, cone->height, cone->diam / 2.0);
	rot = mat4_rotation(normal);
	inv = mat4_mult_mat4(&rot, &scale);
	inv = mat4_mult_mat4(&trans, &inv);
	inv = mat4_inverse(&inv);
	return (inv);
}

t_vector	cn_normal(t_vector local_point)
{
	t_vector	normal;

	if (local_point.y >= 1.0 - EPSILON)
		return (vector_new(0.0, 1.0, 0.0));
	normal = vector_new(local_point.x, -local_point.y, local_point.z);
	return (vector_normalize(normal));
}

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
