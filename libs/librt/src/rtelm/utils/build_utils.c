/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:17:09 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 17:39:54 by sscheini         ###   ########.fr       */
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

static t_mat4	build_mat4(t_vector position, t_vector normal, t_vector scale)
{
	t_mat4	trans;
	t_mat4	rot;
	t_mat4	scl;

	trans = mat4_translation(position.x, position.y, position.z);
	rot = mat4_rotation(normal);
	scl = mat4_scale(scale.x, scale.y, scale.z);
	trans = mat4_mult_mat4(&trans, &rot);
	return (mat4_mult_mat4(&trans, &scl));
}

void	build_matrixes(t_object *obj, t_vector position, t_vector normal, t_vector scale)
{
	obj->transform.mat = build_mat4(position, normal, scale);
	obj->transform.inv = mat4_inverse(&(obj->transform.mat));
	obj->transform.inv_transpose = mat4_transposed(&obj->transform.inv);
}

t_object	*build_object(t_mlx *mlx, char **arr, int (*builder)(char **, t_object *))
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->mlx = mlx;
	if (builder(arr, obj))
		return (NULL);
	return (obj);
}
