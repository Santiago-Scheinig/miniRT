/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_transforms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:54:21 by aramos-r          #+#    #+#             */
/*   Updated: 2026/03/30 17:31:14 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"

t_mat4	mat4_translation(double tx, double ty, double tz)
{
	t_mat4	res;

	res = mat4_new_identity();
	res.m[0][3] = tx;
	res.m[1][3] = ty;
	res.m[2][3] = tz;
	return (res);
}
