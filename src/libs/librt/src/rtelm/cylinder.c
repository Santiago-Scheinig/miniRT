/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:21:46 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/03 13:48:37 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

t_object	*new_cylinder(char **str)
{
	(void) str;
	return (NULL);
}

t_mat4	cylinder_get_inverse_mat4(t_vector center,
					double diameter,
					t_vector normal,
					double height)
{
	t_mat4	inv;
	t_mat4	trans;
	t_mat4	rot;
	t_mat4	scale;

	trans = mat4_translation(center.x, center.y, center.z);
	scale = mat4_scale(diameter / 2.0, height / 2.0, diameter / 2.0);
	rot = mat4_rotation(normal);
	inv = mat4_inverse(mat4_mult_mat4(trans, mat4_mult_mat4(rot, scale)));
	return (inv);
}

t_vector	cylinder_get_normal(t_vector local_point, void *data)
{
	(void)data;
	if (local_point.y >= 1.0 - EPSILON)
		return (vector_new(0.0, 1.0, 0.0));
	if (local_point.y <= -1.0 + EPSILON)
		return (vector_new(0.0, -1.0, 0.0));
	return (vector_new(local_point.x, 0.0, local_point.z));
}
