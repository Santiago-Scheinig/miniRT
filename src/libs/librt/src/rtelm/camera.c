/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:14:30 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/02 14:54:54 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

t_elem_camera	new_camera(char **str)
{
	t_elem_camera	aux;
	t_vector		aux_v;

	(void) str;
	aux_v.x = 0;
	aux_v.y = 0;
	aux_v.z = 0;
	aux.fov = 0;
	aux.normal = aux_v;
	aux.pos = aux_v;
	return (aux);
}
