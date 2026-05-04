/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:00:00 by aramos-r          #+#    #+#             */
/*   Updated: 2026/05/04 00:00:00 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_bonus.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/*--------------------------------------------------------------------------*/
/*------------------------------- LOAD / FREE --------------------------------*/
/*--------------------------------------------------------------------------*/

t_normal_map	*load_normal_map(char *filepath)
{
	t_normal_map	*nmap;
	int				w;
	int				h;
	int				channels;

	nmap = malloc(sizeof(t_normal_map));
	if (!nmap)
		return (NULL);
	nmap->pixels = stbi_load(filepath, &w, &h, &channels, 3);
	if (!nmap->pixels)
	{
		free(nmap);
		return (NULL);
	}
	nmap->width = w;
	nmap->height = h;
	return (nmap);
}

void	free_normal_map(t_normal_map *nmap)
{
	if (!nmap)
		return;
	if (nmap->pixels)
		stbi_image_free(nmap->pixels);
	free(nmap);
}

/*--------------------------------------------------------------------------*/
/*--------------------------------- TANGENTS ---------------------------------*/
/*--------------------------------------------------------------------------*/

t_vector	plane_tangent(t_vector local_point)
{
	(void)local_point;
	return (vector_new(1.0, 0.0, 0.0));
}

t_vector	sphere_tangent(t_vector local_point)
{
	t_vector	t;

	t = vector_new(-local_point.z, 0.0, local_point.x);
	return (vector_normalize(t));
}

t_vector	cylinder_tangent(t_vector local_point)
{
	t_vector	t;

	t = vector_new(-local_point.z, 0.0, local_point.x);
	return (vector_normalize(t));
}

t_vector	cone_tangent(t_vector local_point)
{
	t_vector	t;

	t = vector_new(-local_point.z, 0.0, local_point.x);
	return (vector_normalize(t));
}

t_vector	paraboloid_tangent(t_vector local_point)
{
	t_vector	t;

	t = vector_new(-local_point.z, 0.0, local_point.x);
	return (vector_normalize(t));
}

t_vector	hyperboloid_tangent(t_vector local_point)
{
	t_vector	t;

	t = vector_new(-local_point.z, 0.0, local_point.x);
	return (vector_normalize(t));
}

/*--------------------------------------------------------------------------*/
/*------------------------------ NORMAL MAP ----------------------------------*/
/*--------------------------------------------------------------------------*/

static t_vector	sample_normal_map(t_normal_map *map, t_uv uv)
{
	int				px;
	int				py;
	int				idx;
	t_vector		rgb;

	px = (int)floor(uv.u * (double)(map->width - 1));
	py = (int)floor(uv.v * (double)(map->height - 1));
	if (px < 0)
		px = 0;
	if (px >= map->width)
		px = map->width - 1;
	if (py < 0)
		py = 0;
	if (py >= map->height)
		py = map->height - 1;
	idx = (py * map->width + px) * 3;
	rgb.x = (double)map->pixels[idx];
	rgb.y = (double)map->pixels[idx + 1];
	rgb.z = (double)map->pixels[idx + 2];
	return (rgb);
}

static t_vector	rgb_to_normal(t_vector rgb)
{
	t_vector	n;

	n.x = (rgb.x / 255.0) * 2.0 - 1.0;
	n.y = (rgb.y / 255.0) * 2.0 - 1.0;
	n.z = (rgb.z / 255.0) * 2.0 - 1.0;
	return (vector_normalize(n));
}

static t_vector	compute_tangent_world(t_hit hit, t_vector local_point)
{
	t_vector	t;
	t_vector	tw;

	t = hit.obj->c_tangent(local_point);
	tw = vector_mult_mat4_dir(t, &hit.obj->transform.inv);
	return (vector_normalize(
			vector_sub_vector(tw,
				vector_mult_scalar(hit.surf_normal,
					vector_dot_product(hit.surf_normal, tw)))));
}

static t_vector	sample_tangent_normal(t_hit hit, t_vector local_point)
{
	t_uv	uv;
	t_vector	rgb;

	uv = hit.obj->c_uv_map(local_point);
	rgb = sample_normal_map(hit.obj->material.normal_map, uv);
	return (rgb_to_normal(rgb));
}

t_vector	get_perturbed_normal(t_hit hit, t_vector local_point)
{
	t_vector	tangent;
	t_vector	bitangent;
	t_vector	normal_t;
	t_vector	perturbed;

	if (!hit.obj->material.normal_map || !hit.obj->c_tangent)
		return (hit.surf_normal);
	tangent = compute_tangent_world(hit, local_point);
	bitangent = vector_cross_product(hit.surf_normal, tangent);
	normal_t = sample_tangent_normal(hit, local_point);
	perturbed = vector_sum_vector(
			vector_sum_vector(vector_mult_scalar(tangent, normal_t.x),
				vector_mult_scalar(bitangent, normal_t.y)),
			vector_mult_scalar(hit.surf_normal, normal_t.z));
	return (vector_normalize(perturbed));
}
