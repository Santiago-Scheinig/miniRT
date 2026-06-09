/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtelm_private_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:04:14 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 17:38:46 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTELM_PRIVATE_BONUS_H
# define RTELM_PRIVATE_BONUS_H

# include "rtelm.h"

double		cn_calc_cap_dist(t_ray local_ray);

t_roots		cn_calc_roots(t_ray local_ray);

double		cn_calc_sides_intersection(t_ray local_ray);

t_roots		hb_get_roots(t_ray local_ray);

double		hb_calc_cap_dist(t_ray local_ray, double height);

double		hb_calc_ends_intersection(t_ray local_ray);

t_vector	hb_calc_tangent(t_vector local_point);

t_uv		hb_calc_uv_map(t_vector local_point);

t_roots		pb_calc_roots(t_ray local_ray);

double		pb_calc_cap_dist(t_ray local_ray);

t_vector	pb_calc_tangent(t_vector local_point);

t_uv		pb_calc_uv_map(t_vector local_point);

int			build_add_att(t_object *obj, char **arr);

#endif