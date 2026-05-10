/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parabole_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:00:00 by aramos-r          #+#    #+#             */
/*   Updated: 2026/05/04 21:23:30 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_bonus.h"

/**
 * identifier: pb
 * x, y, z coordinates of the vertex of the paraboloid: 50.0,0.0,20.6
 * 3D normalized vector of axis of paraboloid: 0.0,1.0,0.0
 * the paraboloid diameter at the opening: 14.2
 * the paraboloid height (from vertex to opening): 21.42
 * R, G, B colors in the range [0,255]: 10, 0, 255
 * The bonus extra parameters (reflection and checkers)
 * Example: pb 50.0,0.0,20.6 0.0,1.0,0.0 14.2 21.42 10,0,255
 */

t_mat4	pb_inv_mat4(t_object *obj, t_vector pos, t_vector normal)
{
	t_elem_parabole	*parabole;
	t_mat4			inv;
	t_mat4			trans;
	t_mat4			rot;
	t_mat4			scale;

	parabole = (t_elem_parabole *) obj->data;
	trans = mat4_translation(pos.x, pos.y, pos.z);
	scale = mat4_scale(parabole->diam / 2.0, parabole->height,
			parabole->diam / 2.0);
	rot = mat4_rotation(normal);
	inv = mat4_mult_mat4(&rot, &scale);
	inv = mat4_mult_mat4(&trans, &inv);
	inv = mat4_inverse(&inv);
	return (inv);
}

t_vector	pb_normal(t_vector local_point)
{
	t_vector	normal;

	if (local_point.y >= 1.0 - EPSILON)
		return (vector_new(0.0, 1.0, 0.0));
	normal = vector_new(2.0 * local_point.x, -1.0, 2.0 * local_point.z);
	return (vector_normalize(normal));
}

/**
 * Computes the quadratic coefficients for a ray-paraboloid side intersection.
 * @param local_ray The ray in the paraboloid's local object space.
 * @return A T_ROOTS containing the solutions to the quadratic equation
 * derived from the canonical paraboloid equation x² + z² - y = 0.
 */
static t_roots	get_parabole_roots(t_ray local_ray)
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

double	pb_intersection(t_ray local_ray)
{
	t_roots		roots;
	t_vector	p1;
	t_vector	p2;
	double		valid_t;

	roots = get_parabole_roots(local_ray);
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
