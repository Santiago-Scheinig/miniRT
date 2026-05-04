/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_at_hit_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:00:00 by aramos-r          #+#    #+#             */
/*   Updated: 2026/05/04 00:00:00 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_bonus.h"

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

static t_vector	get_light_contribution(t_hit hit, t_elem_light_p *light)
{
	t_vector	to_light;
	double		n_dot_l;
	double		diffuse;

	to_light = vector_sub_vector(light->pos, hit.pos);
	to_light = vector_normalize(to_light);
	n_dot_l = vector_dot_product(hit.surf_normal, to_light);
	if (n_dot_l <= 0)
		return (vector_new(0, 0, 0));
	diffuse = light->ratio * n_dot_l;
	return (color_hadamard(
			color_hadamard(hit.obj->material.color, light->color),
			vector_new(diffuse, diffuse, diffuse)));
}

static t_vector	get_specular(t_hit hit, t_elem_light_p *light, t_rtapp *app)
{
	t_vector	to_light;
	t_vector	view_dir;
	t_vector	reflect;
	double		n_dot_l;
	double		r_dot_v;
	double		spec;

	to_light = vector_sub_vector(light->pos, hit.pos);
	to_light = vector_normalize(to_light);
	n_dot_l = vector_dot_product(hit.surf_normal, to_light);
	if (n_dot_l <= 0)
		return (vector_new(0, 0, 0));
	reflect = vector_sum_vector(
			vector_mult_scalar(hit.surf_normal, 2.0 * n_dot_l),
			vector_mult_scalar(to_light, -1.0));
	view_dir = vector_sub_vector(app->camera.pos, hit.pos);
	view_dir = vector_normalize(view_dir);
	r_dot_v = vector_dot_product(reflect, view_dir);
	if (r_dot_v <= 0.0)
		return (vector_new(0, 0, 0));
	spec = light->ratio * pow(r_dot_v, hit.obj->material.shininess);
	return (vector_mult_scalar(light->color, spec));
}

static t_vector	get_puntual_lighting(
	t_hit hit,
	t_list *objs,
	t_rtapp *app,
	t_vector res
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
			tmp_color = get_light_contribution(hit, light);
			res = vector_sum_vector(res, tmp_color);
			specular = get_specular(hit, light, app);
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

	res = vector_new(0, 0, 0);
	tmp_color = hit.obj->material.color;
	tmp_color = color_hadamard(tmp_color, app->ambient.color);
	tmp_color = vector_mult_scalar(tmp_color, app->ambient.ratio);
	res = vector_sum_vector(res, tmp_color);
	res = get_puntual_lighting(hit, objs, app, res);
	return (res);
}
