/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtmth.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:24:57 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/29 17:14:06 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTMTH_H
# define RTMTH_H

# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

/**
 * @brief Creates a new vector with the given x, y, and z components.
 * @param x The x component of the vector, should be a double.
 * @param y The y component of the vector, should be a double.
 * @param z The z component of the vector, should be a double.
 * @return The newly created vector.
 */
t_vector	vector_new(double x, double y, double z);

/**
 * @brief Multiplies a vector by a scalar.
 * @param v The vector to be multiplied.
 * @param scalar The scalar value to multiply the vector by, should be a double.
 * @return The resulting vector after multiplication.
 */
t_vector	vector_mult_scalar(t_vector v, double scalar);

/**
 * @brief Divides a vector by a scalar.
 * @param v The vector to be divided.
 * @param scalar The scalar value to divide the vector by, should be a double.
 * @return The resulting vector after division.
 */
t_vector	vector_div_scalar(t_vector v, double scalar);

/**
 * @brief Sums two vectors together.
 * @param v1 The first vector to be summed.
 * @param v2 The second vector to be summed.
 * @return The resulting vector after summing v1 and v2.
 */
t_vector	vector_sum_vector(t_vector v1, t_vector v2);

/**
 * @brief Subtracts one vector from another.
 * @param v1 The vector to be subtracted from.
 * @param v2 The vector to subtract.
 * @return The resulting vector after subtracting v2 from v1.
 */
t_vector	vector_sub_vector(t_vector v1, t_vector v2);

#endif