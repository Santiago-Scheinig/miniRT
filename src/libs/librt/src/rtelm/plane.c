/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:56:20 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 20:24:36 by aramos-r         ###   ########.fr       */
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
	inv = mat4_inverse(mat4_mult_mat4(rot, trans));
	return (inv);
}
