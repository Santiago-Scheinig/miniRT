/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:56:30 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/01 16:54:15 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"

t_vector	vector_new(double x, double y, double z)
{
	t_vector	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

double	vector_module(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	vector_normalize(t_vector v)
{
	t_vector	result;

	result = vector_div_scalar(v, vector_module(v));
	return (result);
}
