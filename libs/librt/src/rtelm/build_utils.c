/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:17:09 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/20 18:23:12 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

t_vector	build_color(char *str)
{
	t_vector	color;
	char		*next;
	
	next = ft_strchr(str, ',') + 1;
	color.r = ft_atoi(str) / 255.0;
	color.g = ft_atoi(next) / 255.0;
	color.b = ft_atoi(ft_strchr(next, ',') + 1) / 255.0; 
	return (color);
}

t_vector	build_vector(char *str)
{
	t_vector	v;
	char		*next;

	v.x = ft_atod(str);
	next = ft_strchr(str, ',') + 1;
	v.y = ft_atod(next);
	next = ft_strchr(next, ',') + 1;
	v.z = ft_atod(next);
	return (v);
}

void		build_matrixes(t_object *obj,
					t_mat4 (*inv_mtx)(t_object *, t_vector, t_vector),
					t_vector position, t_vector normal)
{
	obj->transform.inv = inv_mtx(obj, position, normal);
	obj->transform.inv_transpose = mat4_transposed(obj->transform.inv);
}

t_object	*build_object(char **arr, int (*builder)(char **, t_object *))
{
	t_object *obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (NULL);
	if (builder(arr, obj))
		return (NULL);
	return (obj);
}