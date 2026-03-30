/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:24:09 by aramos-r          #+#    #+#             */
/*   Updated: 2026/03/30 20:20:42 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"

t_ray	ray_new(t_vector origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_vector	ray_point_at(t_ray ray, double t)
{
	t_vector	point;

	point.x = ray.origin.x + ray.direction.x * t;
	point.y = ray.origin.y + ray.direction.y * t;
	point.z = ray.origin.z + ray.direction.z * t;
	return (point);
}

t_ray	ray_transform(t_ray ray, t_mat4 transform)
{
	t_ray	transformed;
	
	transformed.origin = mat4_mult_vector_point(transform, ray.origin);
	transformed.direction = mat4_mult_vector_dir(transform, ray.direction);
	return (transformed);
}
