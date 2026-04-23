/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit_from_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:43:30 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/23 20:32:02 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_render.h"

t_hit	get_hit_from_ray(t_ray ray, t_list *objs)
{
	t_hit		hit;
	t_ray		local_ray;
	double		dist;
	t_object	*current;

	hit = new_hit();
	while (objs)
	{
		current = (t_object *)objs->content;
		local_ray = ray_transform(ray, current->transform.inv);
		dist = current->c_intersection(local_ray);
		if (dist < INFINITY && dist < hit.distance)
		{
			hit.distance = dist;
			hit.obj = current;
			hit.surf_normal = current->c_normal(ray_point_at(local_ray, dist));
			hit.surf_normal = vector_mult_mat4_dir(hit.surf_normal,
					current->transform.inv_transpose);
			hit.surf_normal = vector_normalize(hit.surf_normal);
		}
		objs = objs->next;
	}
	if (hit.obj)
		hit.pos = ray_point_at(ray, hit.distance);
	return (hit);
}
