/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:58:15 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 20:38:55 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

t_object	*new_sphere(char **str)
{
	(void) str;
	return (NULL);
}

t_mat4	sphere_get_inverse_mat4(t_vector center, double diameter)
{
	t_mat4	inv;
	t_mat4	trans;
	t_mat4	scale;

	trans = mat4_translation(center.x, center.y, center.z);
	scale = mat4_scale(diameter / 2.0, diameter / 2.0, diameter / 2.0);
	inv = mat4_inverse(mat4_mult_mat4(trans, scale));
	return (inv);
}
