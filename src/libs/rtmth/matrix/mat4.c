/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 19:50:51 by aramos-r          #+#    #+#             */
/*   Updated: 2026/03/29 20:21:17 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"

t_mat4	matrix_new_identity(void)
{
	t_mat4	result;

	result.m[0][0] = 1.0;
	result.m[0][1] = 0.0;
	result.m[0][2] = 0.0;
	result.m[0][3] = 0.0;
	result.m[1][0] = 0.0;
	result.m[1][1] = 1.0;
	result.m[1][2] = 0.0;
	result.m[1][3] = 0.0;
	result.m[2][0] = 0.0;
	result.m[2][1] = 0.0;
	result.m[2][2] = 1.0;
	result.m[2][3] = 0.0;
	result.m[3][0] = 0.0;
	result.m[3][1] = 0.0;
	result.m[3][2] = 0.0;
	result.m[3][3] = 1.0;
	return (result);
}

t_mat4	matrix_transposed(t_mat4 mat)
{
	t_mat4	res;

	res.m[0][0] = mat.m[0][0];
	res.m[0][1] = mat.m[1][0];
	res.m[0][2] = mat.m[2][0];
	res.m[0][3] = mat.m[3][0];
	res.m[1][0] = mat.m[0][1];
	res.m[1][1] = mat.m[1][1];
	res.m[1][2] = mat.m[2][1];
	res.m[1][3] = mat.m[3][1];
	res.m[2][0] = mat.m[0][2];
	res.m[2][1] = mat.m[1][2];
	res.m[2][2] = mat.m[2][2];
	res.m[2][3] = mat.m[3][2];
	res.m[3][0] = mat.m[0][3];
	res.m[3][1] = mat.m[1][3];
	res.m[3][2] = mat.m[2][3];
	res.m[3][3] = mat.m[3][3];
	return (res);
}
