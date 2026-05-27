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

#include "rtelm.h"

double	cn_calc_cap_dist(t_ray local_ray);

t_roots	cn_calc_roots(t_ray local_ray);

double	cn_calc_sides_intersection(t_ray local_ray);

t_roots	hb_get_roots(t_ray local_ray);

t_roots	pb_calc_roots(t_ray local_ray);



int	build_add_att(t_object *obj, char **arr);

#endif