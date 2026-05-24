/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_cat_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 19:56:57 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 17:28:33 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "../.include/rtelm_private.h"

/**
 * Computes the quadratic coefficients for a ray-paraboloid side intersection.
 * @param local_ray The ray in the paraboloid's local object space.
 * @return A T_ROOTS containing the solutions to the quadratic equation
 * derived from the canonical paraboloid equation x² + z² - y = 0.
 */
t_roots	pb_calc_roots(t_ray local_ray)
{
	double	a;
	double	b;
	double	c;

	a = (local_ray.direction.x * local_ray.direction.x)
		+ (local_ray.direction.z * local_ray.direction.z);
	b = 2.0 * (local_ray.origin.x * local_ray.direction.x
			+ local_ray.origin.z * local_ray.direction.z)
		- local_ray.direction.y;
	c = (local_ray.origin.x * local_ray.origin.x)
		+ (local_ray.origin.z * local_ray.origin.z)
		- local_ray.origin.y;
	return (solve_quadratic(a, b, c));
}