/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_at_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:09:21 by aramos-r          #+#    #+#             */
/*   Updated: 2026/06/15 15:50:03 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_render.h"

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
	t_vector	res;
	double		tmp;

	to_light = vector_sub_vector(light->pos, hit.pos);
	to_light = vector_normalize(to_light);
	n_dot_l = vector_dot_product(hit.surf_normal, to_light);
	if (n_dot_l <= 0)
		return (vector_new(0, 0, 0));
	tmp = light->ratio * n_dot_l;
	res = vector_mult_scalar(hit.obj->material.color, tmp);
	return (res);
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

	light_node = app->lights;
	while (light_node)
	{
		light = (t_elem_light_p *)light_node->content;
		if (!is_in_shadow(hit, light, objs))
		{
			tmp_color = get_light_contribution(hit, light);
			res = vector_sum_vector(res, tmp_color);
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
