/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 19:55:27 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 17:28:45 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "../.include/rtelm_private.h"

/**
 * Computes the quadratic coefficients for a ray-hyperboloid intersection.
 * @param local_ray The ray in the hyperboloid's local object space.
 * @return A T_ROOTS containing the solutions to the quadratic equation
 * derived from the canonical hyperboloid equation x² + z² - y² = 1.
 */
t_roots	hb_get_roots(t_ray local_ray)
{
	double	a;
	double	b;
	double	c;

	a = (local_ray.direction.x * local_ray.direction.x)
		- (local_ray.direction.y * local_ray.direction.y)
		+ (local_ray.direction.z * local_ray.direction.z);
	b = 2.0 * (local_ray.origin.x * local_ray.direction.x
			- local_ray.origin.y * local_ray.direction.y
			+ local_ray.origin.z * local_ray.direction.z);
	c = (local_ray.origin.x * local_ray.origin.x)
		- (local_ray.origin.y * local_ray.origin.y)
		+ (local_ray.origin.z * local_ray.origin.z) - 1.0;
	return (solve_quadratic(a, b, c));
}