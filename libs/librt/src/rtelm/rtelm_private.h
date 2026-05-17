/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtelm_private.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:04:14 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/17 15:46:37 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
double		cy_intersection(t_ray local_ray);

/**
 * Converts a comma-separated coordinate string to a 3D vector.
 * @param str The string containing the coordinates in "X,Y,Z" format.
 * @return A T_VECTOR with the x, y, z components parsed from STR.
 * @note Uses ft_atod for parsing, does not validate input format.
 */
t_vector	build_vector(char *str);

/**
 * Converts a comma-separated RGB string to a normalized color vector.
 * @param str The string containing the RGB values in "R,G,B" format.
 * @return A T_VECTOR with r, g, b components normalized to the 0.0-1.0 range.
 * @note Expects integer values in the 0-255 range. Does not validate input.
 */
t_vector	build_color(char *str);

/**
 * Builds and stores the inverse and inverse transpose matrices for an object.
 * @param obj The object to build the matrices for.
 * @param inv_mtx A function pointer to the object-specific inverse matrix
 * builder, which takes the object, position and normal as arguments.
 * @param position The world space position of the object.
 * @param normal The orientation normal of the object.
 * @note Position and normal are consumed into the matrices and do not need
 * to be stored after this call. The inv_transpose is used for correct
 * normal transformation during lighting calculations.
 */
void		build_matrixes(
				t_object *obj,
				t_vector position, t_vector normal, t_vector scale
				);
