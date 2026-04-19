/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:13:30 by aramos-r          #+#    #+#             */
/*   Updated: 2026/03/29 17:59:22 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"

t_vector	vector_sum_vector(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	vector_sub_vector(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

double	vector_distance_points(t_vector p1, t_vector p2)
{
	t_vector	diff;
	double		distance;

	diff = vector_sub_vector(p1, p2);
	distance = vector_module(diff);
	return (distance);
}

double	vector_dot_product(t_vector v1, t_vector v2)
{
	double	dot_product;

	dot_product = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (dot_product);
}

t_vector	vector_cross_product(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}
