/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:58:15 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/11 20:52:37 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

double	sphere_intersection(t_ray local_ray)
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

t_vector	sphere_normal(t_vector local_point)
{
	return (local_point);
}

static void	build_sphere_data(char **str, t_elem_sphere *sphere, t_object *obj)
{
	char	*next;
	
	sphere->pos.x = ft_atod(str[1]);
	next = ft_strchr(str[1], ',') + 1;
	sphere->pos.y = ft_atod(next);
	next = ft_strchr(str[1], ',') + 1;
	sphere->pos.z = ft_atod(next);
	sphere->diam = ft_atod(str[2]);
	sphere->rgb = ft_atod(str[3]);
	obj->data = sphere;
}

t_object	*new_sphere(char **str)
{
	t_elem_sphere	*new_sphere;
	t_object		*new_object;

	new_sphere = ft_calloc(1, sizeof(t_elem_sphere));
	if (!new_sphere)
		return (NULL);
	new_object = ft_calloc(1, sizeof(t_object));
	if (!new_object)
	{
		free(new_sphere);
		return (NULL);
	}
	build_sphere_data(str, new_sphere, new_object);
	build_matrixes(new_object, &sphere_inverse_mat4);
	new_object->c_intersection = &sphere_intersection;
	new_object->c_normal = &sphere_normal;
	return (new_object);
}
