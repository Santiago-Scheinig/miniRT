/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_at_hit_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:00:00 by aramos-r          #+#    #+#             */
/*   Updated: 2026/05/21 19:39:39 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_bonus.h"

t_vector	get_checker_color(t_uv uv)
{
	int	iu;
	int	iv;

	iu = (int)floor(uv.u * CHECKER_SCALE);
	iv = (int)floor(uv.v * CHECKER_SCALE);
	if ((iu + iv) % 2 == 0)
		return (vector_new(1.0, 1.0, 1.0));
	return (vector_new(0.0, 0.0, 0.0));
}

static t_vector	rgb_to_normal(t_vector rgb)
{
	t_vector	n;

	n.x = (rgb.x / 255.0) * 2.0 - 1.0;
	n.y = (rgb.y / 255.0) * 2.0 - 1.0;
	n.z = (rgb.z / 255.0) * 2.0 - 1.0;
	return (vector_normalize(n));
}

static int	is_in_shadow(t_hit hit, t_elem_light_p *light, t_list *objs)
{
	t_vector	to_light;
	t_ray		shadow_ray;
	t_hit		shadow_hit;

	to_light = vector_sub_vector(light->pos, hit.pos);
	shadow_ray = ray_new(vector_sum_vector(
				hit.pos,
				vector_mult_scalar(hit.surf_normal, EPSILON)),
			vector_normalize(to_light));
	shadow_hit = get_hit_from_ray(shadow_ray, objs);
	return (shadow_hit.obj && shadow_hit.distance < vector_module(to_light));
}

static t_vector	get_light_contribution(t_hit hit, t_elem_light_p *light,
	t_vector mat_color, t_vector n)
{
	t_vector	to_light;
	double		n_dot_l;
	double		diffuse;

	to_light = vector_sub_vector(light->pos, hit.pos);
	to_light = vector_normalize(to_light);
	n_dot_l = vector_dot_product(n, to_light);
	if (n_dot_l <= 0)
		return (vector_new(0, 0, 0));
	diffuse = light->ratio * n_dot_l;
	return (color_hadamard(
			color_hadamard(mat_color, light->color),
			vector_new(diffuse, diffuse, diffuse)));
}

static t_vector	get_specular(t_hit hit, t_elem_light_p *light,
	t_rtapp *app, t_vector mat_color, t_vector n)
{
	t_vector	to_light;
	t_vector	view_dir;
	t_vector	reflect;
	double		n_dot_l;
	double		r_dot_v;
	double		spec;

	to_light = vector_sub_vector(light->pos, hit.pos);
	to_light = vector_normalize(to_light);
	n_dot_l = vector_dot_product(n, to_light);
	if (n_dot_l <= 0)
		return (vector_new(0, 0, 0));
	reflect = vector_sum_vector(
			vector_mult_scalar(n, 2.0 * n_dot_l),
			vector_mult_scalar(to_light, -1.0));
	view_dir = vector_sub_vector(app->camera.pos, hit.pos);
	view_dir = vector_normalize(view_dir);
	r_dot_v = vector_dot_product(reflect, view_dir);
	if (r_dot_v <= 0.0)
		return (vector_new(0, 0, 0));
	spec = light->ratio * pow(r_dot_v, hit.obj->material.shininess);
	return (vector_mult_scalar(mat_color, spec));
}

static t_vector	get_puntual_lighting(
	t_hit hit,
	t_list *objs,
	t_rtapp *app,
	t_vector res,
	t_vector mat_color,
	t_vector lighting_normal
)
{
	t_list			*light_node;
	t_elem_light_p	*light;
	t_vector		tmp_color;
	t_vector		specular;

	light_node = app->lights;
	while (light_node)
	{
		light = (t_elem_light_p *)light_node->content;
		if (!is_in_shadow(hit, light, objs))
		{
			tmp_color = get_light_contribution(hit, light, mat_color,
					lighting_normal);
			res = vector_sum_vector(res, tmp_color);
			specular = get_specular(hit, light, app, mat_color,
					lighting_normal);
			res = vector_sum_vector(res, specular);
		}
		light_node = light_node->next;
	}
	return (res);
}

t_vector	get_color_at_hit(
	t_hit hit,
	t_list *objs,
	t_rtapp *app
)
{
	t_vector	res;
	t_vector	tmp_color;
	t_vector	mat_color;
	t_vector	local_point;
	t_uv		uv;
	t_vector	lighting_normal;

	res = vector_new(0, 0, 0);
	local_point = vector_mult_mat4_point(hit.pos, &hit.obj->transform.inv);
	if (hit.obj->material.is_checker)
	{
		uv = hit.obj->c_uv_map(local_point);
		mat_color = get_checker_color(uv);
	}
	else
		mat_color = hit.obj->material.color;
	if (hit.obj->material.normal_map && hit.obj->c_tangent)
		lighting_normal = get_perturbed_normal(hit, local_point);
	else
		lighting_normal = hit.surf_normal;
	tmp_color = color_hadamard(mat_color, app->ambient.color);
	tmp_color = vector_mult_scalar(tmp_color, app->ambient.ratio);
	res = vector_sum_vector(res, tmp_color);
	res = get_puntual_lighting(hit, objs, app, res, mat_color,
			lighting_normal);
	return (res);
}
