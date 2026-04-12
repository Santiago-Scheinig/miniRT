/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:56:20 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/11 20:54:08 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

t_mat4	plane_get_inverse_mat4(t_vector point, t_vector normal);

static double	plane_intersection(t_ray local_ray)
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

static t_vector	plane_normal(t_vector local_point)
{
	(void) local_point;
	return (vector_new(0.0, 1.0, 0.0));
}

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
	build_matrixes(new_object, &plane_inverse_mat4);
	new_object->c_normal = &plane_normal;
	new_object->c_intersection = &plane_intersection;
	return (new_object);
}
