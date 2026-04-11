/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:56:20 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 21:20:16 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

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

//static void	build_plane_matrixes();

static void build_plane_data(char **str, t_elem_plane *plane, t_object *obj)
{
	char	*next;

	plane->pos.x = ft_atod(str[1]);
	next = ft_strchr(str[1], ',') + 1;
	plane->pos.y = ft_atod(next);
	next = ft_strchr(next, ',') + 1;
	plane->pos.z = ft_atod(next);
	plane->normal.x = ft_atod(str[2]);
	next = ft_strchr(str[2], ',') + 1;
	plane->normal.y = ft_atod(next);
	next = ft_strchr(next, ',') + 1;
	plane->normal.z = ft_atod(next);
	plane->rgb = ft_atod(str[3]);
	obj->data = plane;
}

t_object	*new_plane(char **str)
{
	t_elem_plane	*new_plane;
	t_object		*new_object;

	new_plane = ft_calloc(1, sizeof(t_elem_plane));
	if (!new_plane)
		return (NULL);
	new_object = ft_calloc(1, sizeof(t_object));
	if (!new_object)
	{
		free(new_plane);
		return (NULL);
	}
	build_plane_data(str, new_plane, new_object);
	//build_plane_matrixes()
	//new_object->get_normal = ;
	//new_object->intersection = ;
	return (new_object);
}
