/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtmth.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:24:57 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/30 19:50:50 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTMTH_H
# define RTMTH_H
# define EPSILON 0.00001
# ifndef TRUE
#  define TRUE 1
# endif
# ifndef FALSE
#  define FALSE 0
# endif

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
 * @brief Structure to hold the results of solving a quadratic equation.
 * @param has_solutions An integer flag indicating whether
 * the equation has real solutions (1) or not (0).
 * @param sol1 The first solution of the equation, if it exists.
 * If there are no solutions, this value is undefined.
 * @param sol2 The second solution of the equation, if it exists.
 * If there are no solutions, this value is undefined.
 * @note If the equation has only one solution (i.e., a repeated root),
 * both sol1 and sol2 will contain the same value.
 */
typedef struct s_roots
{
	int		has_solutions;
	double	sol1;
	double	sol2;
}	t_roots;

/**
 * @brief Structure to represent a ray in 3D space,
 * defined by an origin point and a direction vector.
 * @param origin The starting point of the ray, represented as a vector.
 * @param direction The direction of the ray, represented as a vector.
 * @note The direction vector should allways be normalized
 * in the standard space (i.e., have a magnitude of 1)
 * to ensure consistent behavior when performing ray calculations.
 */
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

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

/**
 * @brief Creates a new rotation matrix for a rotation
 * around the x-axis by the given angle.
 * @param angle The angle of rotation in radians, should be a double.
 * @return The newly created rotation matrix.
 * @note The resulting matrix will have the form:
 * @note [ 1 0 0 0 ]
 * @note [ 0 cos(angle) -sin(angle) 0 ]
 * @note [ 0 sin(angle) cos(angle) 0 ]
 * @note [ 0 0 0 1 ]
 */
t_mat4		mat4_rotation_x(double angle);

/**
 * @brief Creates a new rotation matrix for a rotation
 * around the y-axis by the given angle.
 * @param angle The angle of rotation in radians, should be a double.
 * @return The newly created rotation matrix.
 * @note The resulting matrix will have the form:
 * @note [ cos(angle) 0 sin(angle) 0 ]
 * @note [ 0 1 0 0 ]
 * @note [ -sin(angle) 0 cos(angle) 0 ]
 * @note [ 0 0 0 1 ]
 */
t_mat4		mat4_rotation_y(double angle);

/**
 * @brief Creates a new rotation matrix for a rotation
 * around the z-axis by the given angle.
 * @param angle The angle of rotation in radians, should be a double.
 * @return The newly created rotation matrix.
 * @note The resulting matrix will have the form:
 * @note [ cos(angle) -sin(angle) 0 0 ]
 * @note [ sin(angle) cos(angle) 0 0 ]
 * @note [ 0 0 1 0 ]
 * @note [ 0 0 0 1 ]
 */
t_mat4		mat4_rotation_z(double angle);

/**
 * @brief Creates a new scaling matrix for the given scaling factors.
 * This matrix can be used to scale points in 3D space by the specified
 * amounts along the x, y, and z axes.
 * @param sx The scaling factor along the x-axis, should be a double.
 * @param sy The scaling factor along the y-axis, should be a double.
 * @param sz The scaling factor along the z-axis, should be a double.
 * @return The newly created scaling matrix.
 * @note The resulting matrix will have the form:
 * @note [ sx 0 0 0 ]
 * @note [ 0 sy 0 0 ]
 * @note [ 0 0 sz 0 ]
 * @note [ 0 0 0 1 ]
 */
t_mat4		mat4_scale(double sx, double sy, double sz);

/**
 * @brief Solves a quadratic equation of the form ax^2 + bx + c = 0.
 * @param a The coefficient of x^2, should be a double.
 * @param b The coefficient of x, should be a double.
 * @param c The constant term, should be a double.
 * @return A structure containing the solutions of the equation.
 * @note If the equation has real solutions,
 * the has_solutions field will be set to 1,
 * and sol1 and sol2 will contain the two solutions
 * (which may be the same if there is a repeated root).
 * @note If the equation does not have real solutions,
 * the has_solutions field will be set to 0, and sol1 and sol2 will be undefined.
 */
t_roots		solve_quadratic(double a, double b, double c);

/**
 * @brief Creates a new ray with the given origin and direction.
 * @param origin The starting point of the ray, represented as a vector.
 * @param direction The direction of the ray, represented as a vector.
 * @return The newly created ray.
 * @warning The direction vector should be normalized
 * if working in the normal space
 * @warning If the direction vector is (0.0, 0.0, 0.0),
 * the ray will be created with a zero direction and
 * following ray calculations may not behave as expected.
 */
t_ray		ray_new(t_vector origin, t_vector direction);

/**
 * @brief Calculates a point along the ray at a given
 * distance t from the origin.
 * @param ray The ray for which to calculate the point.
 * @param t The distance from the ray's origin
 * to the point, should be a double.
 * @return The point along the ray at distance t
 * from the origin, represented as a vector.
 * @note The point is calculated using the formula: origin + t * direction.
 * @warning The direction vector of the ray should be normalized
 */
t_vector	ray_point_at(t_ray ray, double t);

#endif