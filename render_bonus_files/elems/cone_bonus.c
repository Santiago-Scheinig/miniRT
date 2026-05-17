/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:19:21 by aramos-r          #+#    #+#             */
/*   Updated: 2026/05/17 17:28:32 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_bonus.h"

static t_vector	cn_normal(t_vector local_point)
{
	t_vector	normal;

	if (local_point.y >= 1.0 - EPSILON)
		return (vector_new(0.0, 1.0, 0.0));
	normal = vector_new(local_point.x, -local_point.y, local_point.z);
	return (vector_normalize(normal));
}

int	build_cn(char **str, t_object *obj)
{
	t_elem_quadric	*data;
	t_vector		position;
	t_vector		normal;
	t_vector		scale;

	position = build_vector(str[1]);
	normal = build_vector(str[2]);
	if (!normal.x && !normal.y && !normal.z)
		return (1);
	data = ft_calloc(1, sizeof(t_elem_quadric));
	if (!data)
		return (1);
	data->radius = ft_atod(str[2]) / 2.0;
	data->height = ft_atod(str[4]);
	obj->material.color = build_color(str[3]);
	obj->data = data;
	obj->c_intersection = &cn_intersection;
	obj->c_normal = &cn_normal;
	scale.x = data->radius;
	scale.y = data->height;
	scale.z = data->radius;
	build_matrixes(obj, position, normal, scale);
	return (0);
}