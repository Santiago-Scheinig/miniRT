/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:56:20 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 17:34:04 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "../.include/rtelm_private.h"

/**
 * Computes the intersection distance of a ray with a canonical plane.
 * @param local_ray The ray in the plane's local object space.
 * @return The distance T to the intersection with the XZ plane (Y = 0),
 * or INFINITY if the ray is parallel to the plane or hits behind the origin.
 * @note The canonical plane is the infinite XZ plane with normal (0,1,0).
 */
static double	pl_calc_intersection(t_ray local_ray)
{
	double	t;

	if (fabs(local_ray.direction.y) < EPSILON)
		return (INFINITY);
	t = -local_ray.origin.y / local_ray.direction.y;
	if (t < EPSILON)
		return (INFINITY);
	else
		return (t);
}

/**
 * Returns the constant normal of the canonical plane.
 * @param local_point The point on the plane surface, unused since the
 * normal is constant across the entire plane.
 * @return Always returns (0, 1, 0), the upward facing normal of the
 * canonical XZ plane in local object space.
 */
static t_vector	pl_calc_normal(t_vector local_point)
{
	(void) local_point;
	return (vector_new(0.0, 1.0, 0.0));
}

int	build_pl(char **str, t_object *obj)
{
	t_vector	position;
	t_vector	normal;
	t_vector	scale;

	position = build_vector(str[1]);
	normal = build_vector(str[2]);
	if (!normal.x && !normal.y && !normal.z)
		return (1);
	obj->material.color = build_color(str[3]);
	scale = vector_new(1, 1, 1);
	build_matrixes(obj, position, normal, scale);
	obj->c_intersection = &pl_calc_intersection;
	obj->c_normal = &pl_calc_normal;
	obj->data = NULL;
	return (0);
}
