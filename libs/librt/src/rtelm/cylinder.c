/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:21:46 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/24 12:52:15 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "rtelm_private.h"

/**
 * Computes the inverse transformation matrix for a cylinder object.
 * @param obj The cylinder object containing the T_ELEM_CYLINDER data.
 * @param position The world space position of the cylinder's center.
 * @param normal The orientation normal defining the cylinder's axis.
 * @return The inverse of the cylinder's transformation matrix M = T * R * S.
 * @note The canonical cylinder has radius 1 and height from -1 to 1.
 * Scale is derived from diam / 2 on X and Z, and height / 2 on Y.
 * Position and normal are consumed into the matrix and discarded after.
 */
static t_mat4	cy_inv_mat4(t_object *obj, t_vector position, t_vector normal)
{
	t_elem_cylinder	*cy;
	t_mat4			inv;
	t_mat4			trans;
	t_mat4			rot;
	t_mat4			scale;

	cy = (t_elem_cylinder *) obj->data;
	trans = mat4_translation(position.x, position.y, position.z);
	scale = mat4_scale(cy->diam / 2.0, cy->height / 2.0, cy->diam / 2.0);
	rot = mat4_rotation(normal);
	inv = mat4_mult_mat4(&rot, &scale);
	inv = mat4_mult_mat4(&trans, &inv);
	inv = mat4_inverse(&inv);
	return (inv);
}

/**
 * Computes the object space normal of a cylinder at a given surface point.
 * @param local_point The point on the cylinder surface in local object space.
 * @return The outward facing normal vector at LOCAL_POINT. Returns (0,1,0)
 * for the top cap, (0,-1,0) for the bottom cap, and a radial normal for
 * the side surface.
 * @note Cap detection uses EPSILON tolerance to handle floating point
 * imprecision at the cap boundaries.
 */
static t_vector	cy_normal(t_vector local_point)
{
	if (local_point.y >= 1.0 - EPSILON)
		return (vector_new(0.0, 1.0, 0.0));
	if (local_point.y <= -1.0 + EPSILON)
		return (vector_new(0.0, -1.0, 0.0));
	return (vector_new(local_point.x, 0.0, local_point.z));
}

int	build_cy(char **str, t_object *obj)
{
	t_elem_cylinder	*data;
	t_vector		position;
	t_vector		normal;

	position = build_vector(str[1]);
	normal = build_vector(str[2]);
	if (!normal.x && !normal.y && !normal.z)
		return (1);
	data = ft_calloc(1, sizeof(t_elem_cylinder));
	if (!data)
		return (1);
	data->diam = ft_atod(str[3]);
	data->height = ft_atod(str[4]);
	obj->material.color = build_color(str[5]);
	obj->data = data;
	obj->c_intersection = &cy_intersection;
	obj->c_normal = &cy_normal;
	build_matrixes(obj, &cy_inv_mat4, position, normal);
	return (0);
}
