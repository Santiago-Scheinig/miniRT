/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:56:20 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 19:11:09 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "rtelm_private.h"

static t_mat4	pl_inv_mat4(t_object *obj, t_vector position, t_vector normal)
{
	t_mat4			inv;
	t_mat4			rot;
	t_mat4			trans;

	(void) obj;
	trans = mat4_translation(position.x, position.y, position.z);
	rot = mat4_rotation(normal);
	inv = mat4_inverse(mat4_mult_mat4(trans, rot));
	return (inv);
}

static double	pl_intersection(t_ray local_ray)
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

static t_vector	pl_normal(t_vector local_point)
{
	(void) local_point;
	return (vector_new(0.0, 1.0, 0.0));
}

int	build_pl(char **str, t_object *obj)
{
	t_vector	position;
	t_vector	normal;

	position = build_vector(str[1]);
	normal = build_vector(str[2]);
	if (!normal.x && !normal.y && !normal.z)
		return (1);
	obj->material.color = build_color(str[3]);
	obj->data = NULL;
	obj->c_intersection = &pl_intersection;
	obj->c_normal = &pl_normal;
	build_matrixes(obj, &pl_inv_mat4, position, normal);
	return (0);
}
