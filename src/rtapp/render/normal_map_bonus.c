/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:00:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/29 00:00:00 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_render_bonus.h"

static t_vector	rgb_to_normal(t_vector rgb)
{
	t_vector	n;

	n.x = (rgb.r / 255.0) * 2.0 - 1.0;
	n.y = (rgb.g / 255.0) * 2.0 - 1.0;
	n.z = (rgb.b / 255.0) * 2.0 - 1.0;
	return (vector_normalize(n));
}

static t_vector	sample_normal_map(t_texture *map, t_uv uv)
{
	int			x;
	int			y;
	int			pixel;
	t_vector	rgb;

	if (!map || !map->pixels || !map->img)
		return (vector_new(0.0, 1.0, 0.0));
	x = (int)(uv.u * (map->width - 1));
	y = (int)(uv.v * (map->height - 1));
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= map->width)
		x = map->width - 1;
	if (y >= map->height)
		y = map->height - 1;
	pixel = y * (map->line_len / 4) + x;
	rgb.b = (map->pixels[pixel] & 0xFF);
	rgb.g = ((map->pixels[pixel] >> 8) & 0xFF);
	rgb.r = ((map->pixels[pixel] >> 16) & 0xFF);
	return (rgb_to_normal(rgb));
}

static t_vector	build_bitangent(t_vector normal, t_vector tangent)
{
	return (vector_cross_product(normal, tangent));
}

t_vector	get_perturbed_normal(t_hit hit, t_vector local_point)
{
	t_vector	tangent;
	t_vector	bitangent;
	t_vector	map_normal;
	t_uv		uv;
	t_vector	result;

	if (!hit.obj->c_tangent || !hit.obj->c_uv_map)
		return (hit.surf_normal);
	uv = hit.obj->c_uv_map(local_point);
	map_normal = sample_normal_map(&hit.obj->material.map, uv);
	tangent = hit.obj->c_tangent(local_point);
	tangent = vector_mult_mat4_dir(tangent, &hit.obj->transform.mat);
	tangent = vector_normalize(tangent);
	bitangent = build_bitangent(hit.surf_normal, tangent);
	result = vector_sum_vector(
			vector_sum_vector(
				vector_mult_scalar(tangent, map_normal.x),
				vector_mult_scalar(bitangent, map_normal.y)),
			vector_mult_scalar(hit.surf_normal, map_normal.z));
	return (vector_normalize(result));
}
