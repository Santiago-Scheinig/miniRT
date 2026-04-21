/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit_from_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:43:30 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/21 17:30:01 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_render.h"

t_hit	get_hit_from_ray(t_ray ray, t_object *obj)
{
	t_hit	hit;
	t_ray	local_ray;
	double	distance;

	hit.distance = INFINITY;
	hit.obj = NULL;
	while (obj)
	{
		local_ray = ray_transform(ray, obj->transform.inv);
		distance = obj->c_intersection(local_ray);
		if (distance < INFINITY && distance < hit.distance)
		{
			hit.distance = distance;
			hit.obj = obj;
			hit.surf_normal = obj->c_normal(ray_point_at(local_ray, distance));
		}
	}
	if (hit.obj)
		hit.pos = ray_point_at(ray, hit.distance);
	return (hit);
}
