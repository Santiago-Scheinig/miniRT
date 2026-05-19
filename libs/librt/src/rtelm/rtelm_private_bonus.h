/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtelm_private_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:04:14 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/19 20:22:37 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTELM_PRIVATE_BONUS_H
# define RTELM_PRIVATE_BONUS_H

#include "rtelm.h"

/**
 * Computes the closest intersection distance of a ray with a cylinder.
 * @param local_ray The ray in the cylinder's local object space.
 * @return The smallest valid intersection distance T with either the sides
 * or caps of the cylinder, or INFINITY if no intersection exists.
 * @note The canonical cylinder is centered at the origin with radius 1
 * and height from -1 to 1. Both sides and caps are tested and the closest
 * valid hit is returned.
 */
double		cn_intersection(t_ray local_ray);

#endif