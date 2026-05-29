/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_at_hit_bonus.c                           :+:      :+:    :+:   */
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

static t_vector	calc_diffuse(t_hit hit, t_elem_light_p *light,
	t_shade_ctx ctx)
{
	t_vector	to_light;
	double		n_dot_l;
	double		intensity;

	to_light = vector_normalize(
			vector_sub_vector(light->pos, hit.pos));
	n_dot_l = vector_dot_product(ctx.normal, to_light);
	if (n_dot_l <= 0)
		return (vector_new(0, 0, 0));
	intensity = light->ratio * n_dot_l;
	return (color_hadamard(
			color_hadamard(ctx.mat_color, light->color),
			vector_new(intensity, intensity, intensity)));
}

static t_vector	calc_reflect(t_vector n, t_vector to_light,
	double n_dot_l)
{
	return (vector_sum_vector(
			vector_mult_scalar(n, 2.0 * n_dot_l),
			vector_mult_scalar(to_light, -1.0)));
}

static t_vector	calc_specular(t_hit hit, t_elem_light_p *light,
	t_rtapp *app, t_shade_ctx ctx)
{
	t_vector	to_light;
	double		n_dot_l;
	t_vector	reflect;
	t_vector	view_dir;

	to_light = vector_normalize(
			vector_sub_vector(light->pos, hit.pos));
	n_dot_l = vector_dot_product(ctx.normal, to_light);
	if (n_dot_l <= 0)
		return (vector_new(0, 0, 0));
	reflect = calc_reflect(ctx.normal, to_light, n_dot_l);
	view_dir = vector_normalize(
			vector_sub_vector(app->camera.pos, hit.pos));
	if (vector_dot_product(reflect, view_dir) <= 0.0)
		return (vector_new(0, 0, 0));
	return (vector_mult_scalar(hit.obj->material.specular.color,
			light->ratio * pow(vector_dot_product(reflect, view_dir),
				hit.obj->material.specular.exponent)));
}

static t_vector	process_light(t_hit hit, t_list *objs,
	t_rtapp *app, t_shade_ctx ctx)
{
	t_elem_light_p	*light;
	t_vector		res;

	light = (t_elem_light_p *)objs->content;
	if (is_in_shadow(hit, light, objs))
		return (vector_new(0, 0, 0));
	res = calc_diffuse(hit, light, ctx);
	return (vector_sum_vector(res, calc_specular(hit, light, app, ctx)));
}

static t_vector	sum_lighting(t_hit hit, t_list *objs,
	t_rtapp *app, t_shade_ctx ctx)
{
	t_list	*node;
	t_vector	res;
	t_vector	tmp;

	node = app->lights;
	res = vector_new(0, 0, 0);
	while (node)
	{
		tmp = process_light(hit, node, app, ctx);
		res = vector_sum_vector(res, tmp);
		node = node->next;
	}
	return (res);
}

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

t_vector	get_material_color(t_object *obj, t_vector local_point)
{
	t_uv	uv;

	if (obj->material.is_checker && obj->c_uv_map)
	{
		uv = obj->c_uv_map(local_point);
		return (get_checker_color(uv));
	}
	return (obj->material.color);
}

t_vector	get_lighting_normal(t_hit hit, t_vector local_point)
{
	if (hit.obj->material.map.img && hit.obj->c_tangent)
		return (get_perturbed_normal(hit, local_point));
	return (hit.surf_normal);
}

t_vector	get_color_at_hit(
	t_hit hit,
	t_list *objs,
	t_rtapp *app
)
{
	t_vector		res;
	t_vector		local_point;
	t_shade_ctx		ctx;
	t_vector		ambient;

	local_point = vector_mult_mat4_point(hit.pos, &hit.obj->transform.inv);
	ctx.mat_color = get_material_color(hit.obj, local_point);
	ctx.normal = get_lighting_normal(hit, local_point);
	ambient = color_hadamard(ctx.mat_color, app->ambient.color);
	ambient = vector_mult_scalar(ambient, app->ambient.ratio);
	res = vector_sum_vector(ambient,
			sum_lighting(hit, objs, app, ctx));
	return (res);
}
