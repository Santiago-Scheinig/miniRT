/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:15:16 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/21 18:11:35 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"

uint32_t	translate_color(t_vector color)
{
	color.r = fmax(0.0, fmin(1.0, color.r));
	color.g = fmax(0.0, fmin(1.0, color.g));
	color.b = fmax(0.0, fmin(1.0, color.b));
	return (((uint32_t)(color.r * 255) << 16)
			| ((uint32_t)(color.g * 255) << 8)
			| ((uint32_t)(color.b * 255)));	
}

t_vector	color_hadamard(t_vector ca, t_vector cb)
{
	t_vector c_final;

	c_final.r = ca.r * cb.r;
	c_final.g = ca.g * cb.g;
	c_final.b = ca.b * cb.b;
	return (c_final);
}
