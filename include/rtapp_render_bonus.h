/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_render_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:00:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/29 00:00:00 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_RENDER_BONUS_H
# define RTAPP_RENDER_BONUS_H

# include "rtapp.h"
# include "rtapp_render.h"

# define CHECKER_SCALE 4

typedef struct s_shade_ctx
{
	t_hit		hit;
	t_list		*objs;
	t_vector	mat_color;
	t_vector	normal;
}	t_shade_ctx;

t_vector	get_checker_color(t_uv uv);
t_vector	get_perturbed_normal(t_hit hit, t_vector local_point);
t_vector	get_material_color(t_object *obj, t_vector local_point);
t_vector	get_lighting_normal(t_hit hit, t_vector local_point);
t_vector	sum_lighting(t_shade_ctx ctx, t_rtapp *app);

#endif
