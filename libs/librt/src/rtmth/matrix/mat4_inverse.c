/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_inverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:53:21 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/24 12:52:15 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"

/**
 * Calculates the determinant of a 3x3 matrix.
 * @param m The T_MAT3 to calculate the determinant of.
 * @return The determinant of M as a double.
 * @note Uses the cofactor expansion along the first row.
 */
static double	mat3_determinant(t_mat3 m)
{
	return (m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1])
		- m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0])
		+ m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0])
	);
}

/**
 * Extracts a 3x3 submatrix from a 4x4 matrix by removing a row and column.
 * @param mat The T_MAT4 to extract the submatrix from.
 * @param row The index of the row to remove (0-3).
 * @param col The index of the column to remove (0-3).
 * @return The resulting T_MAT3 after removing ROW and COL from MAT.
 */
static t_mat3	mat4_get_submatrix(const t_mat4 *mat, int row, int col)
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
					res.m[r][c++] = mat->m[i][j];
			}
			r++;
		}
	}
	return (res);
}

/**
 * Calculates the cofactor of a 4x4 matrix at a given row and column.
 * @param mat The T_MAT4 to calculate the cofactor of.
 * @param row The row index of the element (0-3).
 * @param col The column index of the element (0-3).
 * @return The cofactor at (ROW, COL) as a double, negated if the sum
 * of ROW and COL is odd.
 * @note The cofactor is the signed determinant of the submatrix obtained
 * by removing ROW and COL from MAT.
 */
static double	mat4_cofactor(const t_mat4 *mat, int row, int col)
{
	t_mat3	submatrix;
	double	det;

	submatrix = mat4_get_submatrix(mat, row, col);
	det = mat3_determinant(submatrix);
	if ((row + col) % 2 != 0)
		det = -det;
	return (det);
}

t_mat4	mat4_inverse(const t_mat4 *mat)
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
