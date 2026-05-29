/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 19:59:32 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 18:50:48 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "../.include/rtelm_private.h"

#define PLANE_UV_TILE 4.0

static t_vector	pl_calc_tangent(t_vector local_point)
{
	(void)local_point;
	return (vector_new(1.0, 0.0, 0.0));
}

static t_uv	pl_calc_uv_map(t_vector local_point)
{
	t_uv	uv;

	uv.u = fmod(local_point.x / PLANE_UV_TILE, 1.0);
	uv.v = fmod(local_point.z / PLANE_UV_TILE, 1.0);
	if (uv.u < 0.0)
		uv.u += 1.0;
	if (uv.v < 0.0)
		uv.v += 1.0;
	return (uv);
}

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
	build_add_att(obj, &str[4]);
	scale = vector_new(1, 1, 1);
	build_matrixes(obj, position, normal, scale);
	obj->c_intersection = &pl_calc_intersection;
	obj->c_normal = &pl_calc_normal;
	obj->c_tangent = &pl_calc_tangent;
	obj->c_uv_map = &pl_calc_uv_map;
	obj->data = NULL;
	return (0);
}
