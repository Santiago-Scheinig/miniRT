/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:58:15 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 19:11:12 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "rtelm_private.h"

static t_mat4	sp_inv_mat4(t_object *obj, t_vector position, t_vector normal)
{
	t_elem_sphere	*sp;
	t_mat4			inv;
	t_mat4			trans;
	t_mat4			scale;

	(void) normal;
	sp = (t_elem_sphere *) obj->data;
	trans = mat4_translation(position.x, position.y, position.z);
	scale = mat4_scale(sp->diam / 2.0, sp->diam / 2.0, sp->diam / 2.0);
	inv = mat4_inverse(mat4_mult_mat4(trans, scale));
	return (inv);
}

static double	sp_intersection(t_ray local_ray)
{
	double	a;
	double	b;
	double	c;
	t_roots	roots;

	a = vector_dot_product(local_ray.direction, local_ray.direction);
	b = 2.0 * vector_dot_product(local_ray.direction, local_ray.origin);
	c = vector_dot_product(local_ray.origin, local_ray.origin) - 1.0;
	roots = solve_quadratic(a, b, c);
	if (!roots.has_solutions)
		return (INFINITY);
	else if (roots.sol1 > EPSILON)
		return (roots.sol1);
	else if (roots.sol2 > EPSILON)
		return (roots.sol2);
	else
		return (INFINITY);
}

static t_vector	sp_normal(t_vector local_point)
{
	return (local_point);
}

int	build_sp(char **str, t_object *obj)
{
	t_elem_sphere	*data;
	t_vector		position;
	t_vector		normal;
	
	position = build_vector(str[1]);
	ft_memset(&normal, 0, sizeof(t_vector));
	data = ft_calloc(1, sizeof(t_elem_sphere));
	if (!data)
		return (1);
	data->diam = ft_atod(str[2]);
	obj->material.color = build_color(str[3]);
	obj->data = data;
	obj->c_intersection = &sp_intersection;
	obj->c_normal = &sp_normal;
	build_matrixes(obj, &sp_inv_mat4, position, normal);
	return (0);
}
