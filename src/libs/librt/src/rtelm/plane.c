/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:56:20 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/03 13:41:43 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

t_object	*new_plane(char **str)
{
	(void) str;
	return (NULL);
}

t_mat4	plane_get_inverse_mat4(t_vector point, t_vector normal)
{
	t_mat4	inv;
	t_mat4	rot;
	t_mat4	trans;

	trans = mat4_translation(point.x, point.y, point.z);
	rot = mat4_rotation(normal);
	inv = mat4_inverse(mat4_mult_mat4(trans, rot));
	return (inv);
}

double	plane_intersection(t_ray ray, void *data)
{
	double	t;

	(void) data;
	if (fabs(ray.direction.y) < EPSILON)
		return (INFINITY);
	t = -ray.origin.y / ray.direction.y;
	if (t < EPSILON)
		return (INFINITY);
	else
		return (t);
}

t_vector	plane_get_normal(t_vector local_point, void *data)
{
	(void) local_point;
	(void) data;
	return (vector_new(0.0, 1.0, 0.0));
}
