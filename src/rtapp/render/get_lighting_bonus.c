/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lighting_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:00:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/29 00:00:00 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_render_bonus.h"

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

static t_vector	calc_diffuse(t_shade_ctx ctx, t_elem_light_p *light)
{
	t_vector	to_light;
	double		n_dot_l;
	double		intensity;

	to_light = vector_normalize(
			vector_sub_vector(light->pos, ctx.hit.pos));
	n_dot_l = vector_dot_product(ctx.normal, to_light);
	if (n_dot_l <= 0)
		return (vector_new(0, 0, 0));
	intensity = light->ratio * n_dot_l;
	return (color_hadamard(
			color_hadamard(ctx.mat_color, light->color),
			vector_new(intensity, intensity, intensity)));
}

static t_vector	calc_specular(t_shade_ctx ctx,
	t_elem_light_p *light, t_rtapp *app)
{
	t_vector	to_light;
	double		n_dot_l;
	t_vector	reflect;
	t_vector	view_dir;

	to_light = vector_normalize(
			vector_sub_vector(light->pos, ctx.hit.pos));
	n_dot_l = vector_dot_product(ctx.normal, to_light);
	if (n_dot_l <= 0)
		return (vector_new(0, 0, 0));
	reflect = vector_sum_vector(
			vector_mult_scalar(ctx.normal, 2.0 * n_dot_l),
			vector_mult_scalar(to_light, -1.0));
	view_dir = vector_normalize(
			vector_sub_vector(app->camera.pos, ctx.hit.pos));
	if (vector_dot_product(reflect, view_dir) <= 0.0)
		return (vector_new(0, 0, 0));
	return (vector_mult_scalar(ctx.hit.obj->material.specular.color,
			light->ratio * pow(vector_dot_product(reflect, view_dir),
				ctx.hit.obj->material.specular.exponent)));
}

static t_vector	process_light(t_shade_ctx ctx,
	t_list *node, t_rtapp *app)
{
	t_elem_light_p	*light;
	t_vector		res;

	light = (t_elem_light_p *)node->content;
	if (is_in_shadow(ctx.hit, light, ctx.objs))
		return (vector_new(0, 0, 0));
	res = calc_diffuse(ctx, light);
	return (vector_sum_vector(res, calc_specular(ctx, light, app)));
}

t_vector	sum_lighting(t_shade_ctx ctx, t_rtapp *app)
{
	t_list		*node;
	t_vector	res;
	t_vector	tmp;

	node = app->lights;
	res = vector_new(0, 0, 0);
	while (node)
	{
		tmp = process_light(ctx, node, app);
		res = vector_sum_vector(res, tmp);
		node = node->next;
	}
	return (res);
}
