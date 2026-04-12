/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_inverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:53:21 by aramos-r          #+#    #+#             */
/*   Updated: 2026/03/30 01:28:24 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"

static double	mat3_determinant(t_mat3 m)
{
	return (m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1])
		- m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0])
		+ m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0])
	);
}

static t_mat3	mat4_get_submatrix(t_mat4 mat, int row, int col)
{
	t_mat3	res;
	int		i;
	int		j;
	int		r;
	int		c;

	r = 0;
	i = -1;
	while (++i < 4)
	{
		if (i != row)
		{
			c = 0;
			j = -1;
			while (++j < 4)
			{
				if (j != col)
					res.m[r][c++] = mat.m[i][j];
			}
			r++;
		}
	}
	return (res);
}

static double	mat4_cofactor(t_mat4 mat, int row, int col)
{
	t_mat3	submatrix;
	double	det;

	submatrix = mat4_get_submatrix(mat, row, col);
	det = mat3_determinant(submatrix);
	if ((row + col) % 2 != 0)
		det = -det;
	return (det);
}

t_mat4	mat4_inverse(t_mat4 mat)
{
	t_mat4	res;
	int		i;
	int		j;
	double	det;

	det = mat4_determinant(mat);
	if (fabs(det) < EPSILON)
		return (mat4_new_identity());
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.m[j][i] = mat4_cofactor(mat, i, j) / det;
			j++;
		}
		i++;
	}
	return (res);
}
