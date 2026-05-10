/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:00:00 by aramos-r          #+#    #+#             */
/*   Updated: 2026/05/04 21:37:08 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_bonus.h"

/**
 * identifier: hb
 * x, y, z coordinates of the center of the hyperboloid: 50.0,0.0,20.6
 * 3D normalized vector of axis of hyperboloid: 0.0,1.0,0.0
 * the hyperboloid throat diameter: 14.2
 * the hyperboloid height: 21.42
 * R, G, B colors in the range [0,255]: 10, 0, 255
 * The bonus extra parameters (reflection and checkers)
 * Example: hb 50.0,0.0,20.6 0.0,1.0,0.0 14.2 21.42 10,0,255
 */

t_mat4	hb_inv_mat4(t_object *obj, t_vector pos, t_vector normal)
{
	t_elem_hyperboloid	*hyperboloid;
	t_mat4				inv;
	t_mat4				trans;
	t_mat4				rot;
	t_mat4				scale;

	hyperboloid = (t_elem_hyperboloid *) obj->data;
	trans = mat4_translation(pos.x, pos.y, pos.z);
	scale = mat4_scale(hyperboloid->diam / 2.0, hyperboloid->height / 2.0,
			hyperboloid->diam / 2.0);
	rot = mat4_rotation(normal);
	inv = mat4_mult_mat4(&rot, &scale);
	inv = mat4_mult_mat4(&trans, &inv);
	inv = mat4_inverse(&inv);
	return (inv);
}

t_vector	hb_normal(t_vector local_point)
{
	t_vector	normal;

	normal = vector_new(2.0 * local_point.x, -2.0 * local_point.y,
			2.0 * local_point.z);
	return (vector_normalize(normal));
}

/**
 * Computes the quadratic coefficients for a ray-hyperboloid intersection.
 * @param local_ray The ray in the hyperboloid's local object space.
 * @return A T_ROOTS containing the solutions to the quadratic equation
 * derived from the canonical hyperboloid equation x² + z² - y² = 1.
 */
static t_roots	get_hyperboloid_roots(t_ray local_ray)
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

double	hb_intersection(t_ray local_ray)
{
	t_roots		roots;
	t_vector	p1;
	t_vector	p2;
	double		valid_t;

	roots = get_hyperboloid_roots(local_ray);
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
