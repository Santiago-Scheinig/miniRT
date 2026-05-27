/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:58:15 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 17:34:18 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "../.include/rtelm_private.h"

/**
 * Computes the intersection distance of a ray with a canonical unit sphere.
 * @param local_ray The ray in the sphere's local object space.
 * @return The smallest positive distance T to the sphere surface, or
 * INFINITY if no valid intersection exists.
 * @note The canonical sphere is centered at the origin with radius 1.
 * The quadratic coefficients are derived from substituting the ray
 * equation into the sphere equation x² + y² + z² = 1.
 */
static double	sp_calc_intersection(t_ray local_ray)
{
	double	a;
	double	b;
	double	c;
	t_roots	roots;

	a = vector_dot_product(local_ray.direction, local_ray.direction);
	b = 2.0 * vector_dot_product(local_ray.direction, local_ray.origin);
	c = vector_dot_product(local_ray.origin, local_ray.origin) - 1.0;
	roots = solve_quadratic(a, b, c);
	if (!roots.has_solutions)
		return (INFINITY);
	else if (roots.sol1 > EPSILON)
		return (roots.sol1);
	else if (roots.sol2 > EPSILON)
		return (roots.sol2);
	else
		return (INFINITY);
}

/**
 * Returns the normal of a unit sphere at a given surface point.
 * @param local_point The point on the sphere surface in local object space.
 * @return The outward facing normal at LOCAL_POINT, which for a unit sphere
 * centered at the origin is identical to the point itself.
 */
static t_vector	sp_calc_normal(t_vector local_point)
{
	return (local_point);
}

int	build_sp(char **str, t_object *obj)
{
	t_elem_quadric	*data;
	t_vector		position;
	t_vector		normal;
	t_vector		scale;

	position = build_vector(str[1]);
	normal = vector_new(0, 1, 0);
	data = ft_calloc(1, sizeof(t_elem_quadric));
	if (!data)
		return (1);
	data->radius = ft_atod(str[2]) / 2.0;
	obj->material.color = build_color(str[3]);
	scale = vector_new(data->radius, data->radius, data->radius);
	build_matrixes(obj, position, normal, scale);
	obj->c_intersection = &sp_calc_intersection;
	obj->c_normal = &sp_calc_normal;
	obj->data = data;
	return (0);
}
