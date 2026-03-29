/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtmth.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:24:57 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/29 17:38:48 by aramos-r         ###   ########.fr       */
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
 * @brief Calculates the magnitude (length) of a vector.
 * @param v The vector for which to calculate the magnitude.
 * @return The magnitude of the vector as a double.
 */
double		vector_module(t_vector v);

/**
 * @brief Normalizes a vector, returning a new vector with the same direction
 * but a magnitude of 1.
 * @param v The vector to be normalized.
 * @return The normalized vector.
 * @warning If the input vector has a magnitude of 0,
 * the function will return a vector with all components set to 0
 * to avoid division by zero.
 */
t_vector	vector_normalize(t_vector v);

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
 * @warning If the scalar is 0, the function will return a vector
 * with all components set to 0 to avoid division by zero.
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