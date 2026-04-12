/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:21:46 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 19:25:05 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "rtelm_private.h"

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
	inv = mat4_inverse(mat4_mult_mat4(trans, mat4_mult_mat4(rot, scale)));
	return (inv);
}

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
