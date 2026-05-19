/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parabole_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:00:00 by aramos-r          #+#    #+#             */
/*   Updated: 2026/05/19 21:05:33 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm_bonus.h"
#include "rtelm_private.h"

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

static double	pb_intersection(t_ray local_ray)
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

static t_vector	pb_normal(t_vector local_point)
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
	obj->data = data;
	obj->c_intersection = &pb_intersection;
	obj->c_normal = &pb_normal;
	scale.x = data->radius;
	scale.y = data->height;
	scale.z = data->radius;
	build_matrixes(obj, position, normal, scale);
	return (0);
}
