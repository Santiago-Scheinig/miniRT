/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_transforms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:54:21 by aramos-r          #+#    #+#             */
/*   Updated: 2026/03/30 17:52:53 by aramos-r         ###   ########.fr       */
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

t_mat4	mat4_rotation_x(double angle)
{
	t_mat4	res;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	res = mat4_new_identity();
	res.m[1][1] = cos_a;
	res.m[1][2] = -sin_a;
	res.m[2][1] = sin_a;
	res.m[2][2] = cos_a;
	return (res);
}

t_mat4	mat4_rotation_y(double angle)
{
	t_mat4	res;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	res = mat4_new_identity();
	res.m[0][0] = cos_a;
	res.m[0][2] = sin_a;
	res.m[2][0] = -sin_a;
	res.m[2][2] = cos_a;
	return (res);
}

t_mat4	mat4_rotation_z(double angle)
{
	t_mat4	res;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	res = mat4_new_identity();
	res.m[0][0] = cos_a;
	res.m[0][1] = -sin_a;
	res.m[1][0] = sin_a;
	res.m[1][1] = cos_a;
	return (res);
}

t_mat4	mat4_scale(double sx, double sy, double sz)
{
	t_mat4	res;

	res = mat4_new_identity();
	res.m[0][0] = sx;
	res.m[1][1] = sy;
	res.m[2][2] = sz;
	return (res);
}
