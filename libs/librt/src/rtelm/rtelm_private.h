/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtelm_private.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:04:14 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 19:06:51 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

double		cy_intersection(t_ray local_ray);

t_vector	build_vector(char *str);

t_vector	build_color(char *str);

void		build_matrixes(t_object *obj,
					t_mat4 (*inv_mtx)(t_object *, t_vector, t_vector),
					t_vector position, t_vector normal);
