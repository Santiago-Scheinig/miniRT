/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtmth.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:24:57 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/30 17:05:31 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTMTH_H
# define RTMTH_H
# define EPSILON 0.00001

# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_mat4
{
	double	m[4][4];
}	t_mat4;

typedef struct s_mat3
{
	double	m[3][3];
}	t_mat3;

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

/**
 * @brief Calculates the dot product of two vectors.
 * @param v1 The first vector for the dot product.
 * @param v2 The second vector for the dot product.
 * @return The dot product of the two vectors as a double.
 * @note If the vectors are orthogonal, the dot product will be 0.
 */
double		vector_dot_product(t_vector v1, t_vector v2);

/**
 * @brief Calculates the cross product of two vectors.
 * @param v1 The first vector for the cross product.
 * @param v2 The second vector for the cross product.
 * @return The cross product of the two vectors as a new vector.
 * @note The resulting vector is perpendicular to both v1 and v2,
 * and its magnitude is equal to the area
 * of the parallelogram formed by v1 and v2.
 */
t_vector	vector_cross_product(t_vector v1, t_vector v2);

/**
 * @brief Calculates the distance between two points represented as vectors.
 * @param p1 The first point as a vector.
 * @param p2 The second point as a vector.
 * @return The distance between the two points as a double.
 */
double		vector_distance_points(t_vector p1, t_vector p2);

/**
 * @brief Creates a new identity matrix.
 * @return The newly created identity matrix.
 * @note An identity matrix is a square matrix with ones on the main diagonal
 * and zeros elsewhere.
 */
t_mat4		mat4_new_identity(void);

/**
 * @brief Creates a new matrix which is the transposed version of the given one.
 * @param mat The matrix to transpose.
 * @return The transposed matrix.
 */
t_mat4		mat4_transposed(t_mat4 mat);

/**
 * @brief Calculates the determinant of a 4x4 matrix.
 * @param mat The matrix for which to calculate the determinant.
 * @return The determinant of the matrix as a double.
 */
double		mat4_determinant(t_mat4 mat);

/**
 * @brief Creates a new matrix which is the inverse of the given one.
 * @param mat The matrix to invert.
 * @return The inverted matrix.
 * @warning If the matrix is not invertible (i.e., its determinant is 0),
 * the function will return the identity matrix.
 */
t_mat4		mat4_inverse(t_mat4 mat);

/**
 * @brief Multiplies two 4x4 matrices together.
 * @param m1 The first matrix to be multiplied.
 * @param m2 The second matrix to be multiplied.
 * @return The resulting matrix after multiplication.
 * @note Matrix multiplication is not commutative,
 * meaning that mat4_mult_mat4(m1, m2)
 * may not equal mat4_mult_mat4(m2, m1).
 */
t_mat4		mat4_mult_mat4(t_mat4 m1, t_mat4 m2);

/**
 * @brief Creates a new translation matrix for the given translation values.
 * This matrix can be used to translate points in 3D space by the specified
 * amounts along the x, y, and z axes.
 * @param tx The translation amount along the x-axis, should be a double.
 * @param ty The translation amount along the y-axis, should be a double.
 * @param tz The translation amount along the z-axis, should be a double.
 * @return The newly created translation matrix.
 * @note The resulting matrix will have the form:
 * @note [ 1 0 0 tx ]
 * @note [ 0 1 0 ty ]
 * @note [ 0 0 1 tz ]
 * @note [ 0 0 0 1 ]
 */
t_mat4		mat4_translation(double tx, double ty, double tz);

#endif