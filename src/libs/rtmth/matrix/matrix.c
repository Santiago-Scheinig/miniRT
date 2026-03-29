/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 19:50:51 by aramos-r          #+#    #+#             */
/*   Updated: 2026/03/29 19:54:40 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"

t_matrix	matrix_new_identity(void)
{
	t_matrix	result;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				result.m[i][j] = 1.0;
			else
				result.m[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (result);
}
