/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:21:46 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 21:34:26 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

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

//static void	build_cylinder_matrixes();

static void	build_cylinder_data(char **str, t_elem_cylinder *cy, t_object *obj)
{
	char	*next;

	cy->pos.x = ft_atod(str[1]);
	next = ft_strchr(str[1], ',') + 1;
	cy->pos.y = ft_atod(next);
	next = ft_strchr(next, ',') + 1;
	cy->pos.z = ft_atod(next);
	cy->normal.x = ft_atod(str[2]);
	next = ft_strchr(str[2], ',') + 1;
	cy->normal.y = ft_atod(next);
	next = ft_strchr(next, ',') + 1;
	cy->normal.z = ft_atod(next);
	cy->diam = ft_atod(str[3]);
	cy->height = ft_atod(str[4]);
	cy->rgb = ft_atod(str[5]);
	obj->data = cy;
}

t_object	*new_cylinder(char **str)
{
	t_elem_cylinder	*new_cylinder;
	t_object		*new_object;

	new_cylinder = ft_calloc(1, sizeof(t_elem_cylinder));
	if (!new_cylinder)
		return (NULL);
	new_object = ft_calloc(1, sizeof(t_object));
	if (!new_object)
	{
		free(new_cylinder);
		return (NULL);
	}
	build_cylinder_data(str, new_cylinder, new_object);
	//build_plane_matrixes();
	//new_object->get_normal = ;
	//new_object->intersection = ;
	return (new_object);
}
