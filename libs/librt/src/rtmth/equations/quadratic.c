/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:52:38 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/12 20:20:18 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"

/**
 * Calculates the discriminant of a quadratic equation ax² + bx + c = 0.
 * @param a The coefficient of x².
 * @param b The coefficient of x.
 * @param c The constant term.
 * @return The discriminant as a double, computed as b² - 4ac.
 * @note A positive discriminant means two real solutions, zero means
 * one repeated solution, and negative means no real solutions.
 */
static double	get_discriminant(double a, double b, double c)
{
	return ((b * b) - (4 * a * c));
}

t_roots	solve_quadratic(double a, double b, double c)
{
	t_roots	res;
	double	discriminant;
	double	sqrt_discriminant;
	double	temp;
	double	inv_denom;

	discriminant = get_discriminant(a, b, c);
	if (discriminant < 0 || fabs(a) < EPSILON)
		res.has_solutions = FALSE;
	else
	{
		res.has_solutions = TRUE;
		sqrt_discriminant = sqrt(discriminant);
		inv_denom = 1.0 / (2.0 * a);
		res.sol1 = (-b + sqrt_discriminant) * inv_denom;
		res.sol2 = (-b - sqrt_discriminant) * inv_denom;
		if (res.sol1 > res.sol2)
		{
			temp = res.sol1;
			res.sol1 = res.sol2;
			res.sol2 = temp;
		}
	}
	return (res);
}
