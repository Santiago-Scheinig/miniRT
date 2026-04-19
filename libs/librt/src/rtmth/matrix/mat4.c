/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 19:50:51 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/04 11:36:09 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"

t_mat4	mat4_new_identity(void)
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

t_mat4	mat4_transposed(t_mat4 mat)
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

double	mat4_determinant(t_mat4 m)
{
	return (
		m.m[0][0] * (m.m[1][1]
			* (m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2])
		- m.m[1][2] * (m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1])
		+ m.m[1][3] * (m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1]))
		- m.m[0][1] * (m.m[1][0]
			* (m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2])
		- m.m[1][2] * (m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0])
		+ m.m[1][3] * (m.m[2][0] * m.m[3][2] - m.m[2][2] * m.m[3][0]))
		+ m.m[0][2] * (m.m[1][0]
			* (m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1])
		- m.m[1][1] * (m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0])
		+ m.m[1][3] * (m.m[2][0] * m.m[3][1] - m.m[2][1] * m.m[3][0]))
		- m.m[0][3] * (m.m[1][0]
			* (m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1])
		- m.m[1][1] * (m.m[2][0] * m.m[3][2] - m.m[2][2] * m.m[3][0])
		+ m.m[1][2] * (m.m[2][0] * m.m[3][1] - m.m[2][1] * m.m[3][0]))
	);
}

t_mat4	mat4_mult_mat4(t_mat4 m1, t_mat4 m2)
{
	t_mat4	res;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.m[i][j] = 0.0;
			k = 0;
			while (k < 4)
			{
				res.m[i][j] += m1.m[i][k] * m2.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (res);
}

t_mat4	mat4_rotation(t_vector normal)
{
	t_vector	right;
	t_vector	forward;
	t_vector	guide;
	t_mat4		res;

	normal = vector_normalize(normal);
	guide = vector_new(0.0, 1.0, 0.0);
	if (fabs(normal.y) > 1.0 - EPSILON)
		guide = vector_new(1.0, 0.0, 0.0);
	right = vector_normalize(vector_cross_product(guide, normal));
	forward = vector_normalize(vector_cross_product(right, normal));
	res = mat4_new_identity();
	res.m[0][0] = right.x;
	res.m[1][0] = right.y;
	res.m[2][0] = right.z;
	res.m[0][1] = normal.x;
	res.m[1][1] = normal.y;
	res.m[2][1] = normal.z;
	res.m[0][2] = forward.x;
	res.m[1][2] = forward.y;
	res.m[2][2] = forward.z;
	return (res);
}
