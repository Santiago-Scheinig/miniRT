/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_at_hit_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:27:37 by aramos-r          #+#    #+#             */
/*   Updated: 2026/06/15 16:27:38 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_render_bonus.h"

t_vector	get_color_at_hit(
	t_hit hit,
	t_list *objs,
	t_rtapp *app
)
{
	t_shade_ctx	ctx;
	t_vector	local_point;
	t_vector	ambient;
	t_vector	res;

	local_point = vector_mult_mat4_point(hit.pos,
			&hit.obj->transform.inv);
	ctx.hit = hit;
	ctx.objs = objs;
	ctx.mat_color = get_material_color(hit.obj, local_point);
	ctx.normal = get_lighting_normal(hit, local_point);
	ambient = color_hadamard(ctx.mat_color, app->ambient.color);
	ambient = vector_mult_scalar(ambient, app->ambient.ratio);
	res = vector_sum_vector(ambient, sum_lighting(ctx, app));
	return (res);
}
