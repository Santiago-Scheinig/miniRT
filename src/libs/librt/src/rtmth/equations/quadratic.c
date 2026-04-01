/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:52:38 by aramos-r          #+#    #+#             */
/*   Updated: 2026/03/30 19:06:14 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"

static double	get_discriminant(double a, double b, double c)
{
	return ((b * b) - (4 * a * c));
}

t_roots	solve_quadratic(double a, double b, double c)
{
	t_roots	res;
	double	discriminant;
	double	sqrt_discriminant;

	discriminant = get_discriminant(a, b, c);
	if (discriminant < 0)
		res.has_solutions = FALSE;
	else
	{
		res.has_solutions = TRUE;
		sqrt_discriminant = sqrt(discriminant);
		res.sol1 = (-b + sqrt_discriminant) / (2 * a);
		res.sol2 = (-b - sqrt_discriminant) / (2 * a);
	}
	return (res);
}
