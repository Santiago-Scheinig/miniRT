/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:56:30 by aramos-r          #+#    #+#             */
/*   Updated: 2026/03/29 17:18:16 by aramos-r         ###   ########.fr       */
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
