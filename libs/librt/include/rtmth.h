/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtmth.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:24:57 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/21 18:46:39 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTMTH_H
# define RTMTH_H
# include <math.h>
# include <stdint.h>

# define EPSILON 0.00001
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# ifndef TRUE
#  define TRUE 1
# endif
# ifndef FALSE
#  define FALSE 0
# endif

/*--------------------------------------------------------------------------*/
/*--------------------------------STRUCTURES--------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Represents a 3D vector usable as either a spatial coordinate or a color.
 * @note The union allows the same data to be accessed as (x, y, z) for
 * geometry or (r, g, b) for color without any conversion or overhead.
 */
typedef union u_vector
{
	struct {double x, y, z;}; // Spatial coordinate access.
	struct {double r, g, b;}; // Normalized color access in 0.0-1.0 range.
}	t_vector;

/**
 * Represents a 4x4 matrix used for 3D transformations.
 * @note Used to encode translation, rotation and scale into a single
 * matrix for ray transformation into object local space.
 */
typedef struct s_mat4
{
	double	m[4][4]; // Row-major matrix components.
}	t_mat4;

/**
 * Represents a 3x3 matrix used for linear transformations.
 * @note Used for operations that do not require translation such as
 * normal transformation and rotation only calculations.
 */
typedef struct s_mat3
{
	double	m[3][3]; // Row-major matrix components.
}	t_mat3;

/**
 * Holds the results of solving a quadratic equation ax² + bx + c = 0.
 * @note If the equation has only one solution (repeated root), both sol1
 * and sol2 contain the same value. If has_solutions is 0, sol1 and sol2
 * are undefined.
 */
typedef struct s_roots
{
	int		has_solutions; // 1 if real solutions exist, 0 otherwise.
	double	sol1;          // Smallest solution of the equation.
	double	sol2;          // Largest solution of the equation.
}	t_roots;

/**
 * Represents a ray in 3D space defined by an origin and a direction.
 * @note The direction vector must always be normalized to ensure
 * consistent behavior in intersection and lighting calculations.
 */
typedef struct s_ray
{
	t_vector	origin;    // Starting point of the ray in world space.
	t_vector	direction; // Normalized direction vector of the ray.
}	t_ray;

/*--------------------------------------------------------------------------*/
/*-------------------------------VECTORIZATION------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Creates a new vector with the given x, y, and z components.
 * @param x The x component of the vector.
 * @param y The y component of the vector.
 * @param z The z component of the vector.
 * @return The newly created T_VECTOR.
 */
t_vector	vector_new(double x, double y, double z);

/**
 * Calculates the magnitude (length) of a vector.
 * @param v The vector for which to calculate the magnitude.
 * @return The magnitude of V as a double.
 */
double		vector_module(t_vector v);

/**
 * Normalizes a vector to a magnitude of 1 preserving its direction.
 * @param v The vector to normalize.
 * @return The normalized vector, or a zero vector if V has magnitude 0.
 * @note If the input vector has a magnitude of 0, returns a zero vector
 * to avoid division by zero.
 */
t_vector	vector_normalize(t_vector v);

/**
 * Multiplies a vector by a scalar.
 * @param v The vector to multiply.
 * @param scalar The scalar value to multiply V by.
 * @return The resulting T_VECTOR after multiplication.
 */
t_vector	vector_mult_scalar(t_vector v, double scalar);

/**
 * Divides a vector by a scalar.
 * @param v The vector to divide.
 * @param scalar The scalar value to divide V by.
 * @return The resulting T_VECTOR after division, or a zero vector if
 * scalar is 0 to avoid division by zero.
 */
t_vector	vector_div_scalar(t_vector v, double scalar);

/**
 * Adds two vectors together.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The resulting T_VECTOR after summing V1 and V2.
 */
t_vector	vector_sum_vector(t_vector v1, t_vector v2);

/**
 * Subtracts one vector from another.
 * @param v1 The vector to subtract from.
 * @param v2 The vector to subtract.
 * @return The resulting T_VECTOR after subtracting V2 from V1.
 */
t_vector	vector_sub_vector(t_vector v1, t_vector v2);

/**
 * Calculates the dot product of two vectors.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The dot product of V1 and V2 as a double.
 * @note Returns 0 if the vectors are orthogonal.
 */
double		vector_dot_product(t_vector v1, t_vector v2);

/**
 * Calculates the cross product of two vectors.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return A T_VECTOR perpendicular to both V1 and V2 with magnitude
 * equal to the area of the parallelogram formed by V1 and V2.
 */
t_vector	vector_cross_product(t_vector v1, t_vector v2);

/**
 * Calculates the distance between two points represented as vectors.
 * @param p1 The first point as a T_VECTOR.
 * @param p2 The second point as a T_VECTOR.
 * @return The distance between P1 and P2 as a double.
 */
double		vector_distance_points(t_vector p1, t_vector p2);

/*--------------------------------------------------------------------------*/
/*---------------------------------MATRIXES---------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Creates a new 4x4 identity matrix.
 * @return The newly created identity T_MAT4.
 * @note An identity matrix has ones on the main diagonal and zeros
 * elsewhere, and leaves vectors unchanged when multiplied.
 */
t_mat4		mat4_new_identity(void);

/**
 * Creates the transposed version of a 4x4 matrix.
 * @param mat The matrix to transpose.
 * @return The transposed T_MAT4.
 */
t_mat4		mat4_transposed(t_mat4 mat);

/**
 * Calculates the determinant of a 4x4 matrix.
 * @param mat The matrix for which to calculate the determinant.
 * @return The determinant of MAT as a double.
 */
double		mat4_determinant(t_mat4 mat);

/**
 * Creates the inverse of a 4x4 matrix.
 * @param mat The matrix to invert.
 * @return The inverted T_MAT4, or the identity matrix if MAT is not
 * invertible (determinant is 0).
 */
t_mat4		mat4_inverse(t_mat4 mat);

/**
 * Multiplies two 4x4 matrices together.
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return The resulting T_MAT4 after multiplication.
 * @note Matrix multiplication is not commutative — mat4_mult_mat4(m1, m2)
 * may not equal mat4_mult_mat4(m2, m1).
 */
t_mat4		mat4_mult_mat4(t_mat4 m1, t_mat4 m2);

/**
 * Creates a translation matrix for the given translation values.
 * @param tx The translation amount along the x-axis.
 * @param ty The translation amount along the y-axis.
 * @param tz The translation amount along the z-axis.
 * @return The newly created translation T_MAT4.
 * @note The resulting matrix has the form:
 * @note [ 1  0  0  tx ]
 * @note [ 0  1  0  ty ]
 * @note [ 0  0  1  tz ]
 * @note [ 0  0  0  1  ]
 */
t_mat4		mat4_translation(double tx, double ty, double tz);

/**
 * Creates a rotation matrix for a rotation around the x-axis.
 * @param angle The angle of rotation in radians.
 * @return The newly created x-axis rotation T_MAT4.
 * @note The resulting matrix has the form:
 * @note [ 1  0           0          0 ]
 * @note [ 0  cos(angle) -sin(angle) 0 ]
 * @note [ 0  sin(angle)  cos(angle) 0 ]
 * @note [ 0  0           0          1 ]
 */
t_mat4		mat4_rotation_x(double angle);

/**
 * Creates a rotation matrix for a rotation around the y-axis.
 * @param angle The angle of rotation in radians.
 * @return The newly created y-axis rotation T_MAT4.
 * @note The resulting matrix has the form:
 * @note [ cos(angle)  0  sin(angle) 0 ]
 * @note [ 0           1  0          0 ]
 * @note [-sin(angle)  0  cos(angle) 0 ]
 * @note [ 0           0  0          1 ]
 */
t_mat4		mat4_rotation_y(double angle);

/**
 * Creates a rotation matrix for a rotation around the z-axis.
 * @param angle The angle of rotation in radians.
 * @return The newly created z-axis rotation T_MAT4.
 * @note The resulting matrix has the form:
 * @note [ cos(angle) -sin(angle) 0 0 ]
 * @note [ sin(angle)  cos(angle) 0 0 ]
 * @note [ 0           0          1 0 ]
 * @note [ 0           0          0 1 ]
 */
t_mat4		mat4_rotation_z(double angle);

/**
 * Creates a rotation matrix that aligns the Y axis with a normal vector.
 * @param normal The target orientation normal vector.
 * @return The newly created rotation T_MAT4.
 */
t_mat4		mat4_rotation(t_vector normal);

/**
 * Creates a scaling matrix for the given scaling factors.
 * @param sx The scaling factor along the x-axis.
 * @param sy The scaling factor along the y-axis.
 * @param sz The scaling factor along the z-axis.
 * @return The newly created scaling T_MAT4.
 * @note The resulting matrix has the form:
 * @note [ sx 0  0  0 ]
 * @note [ 0  sy 0  0 ]
 * @note [ 0  0  sz 0 ]
 * @note [ 0  0  0  1 ]
 */
t_mat4		mat4_scale(double sx, double sy, double sz);

/*--------------------------------------------------------------------------*/
/*--------------------------------RAYCASTING--------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Creates a new ray with the given origin and direction.
 * @param origin The starting point of the ray in world space.
 * @param direction The direction of the ray, should be normalized.
 * @return The newly created T_RAY.
 * @note If direction is (0, 0, 0) ray calculations will not behave
 * as expected.
 */
t_ray		ray_new(t_vector origin, t_vector direction);

/**
 * Calculates a point along a ray at a given distance from its origin.
 * @param ray The ray to evaluate.
 * @param t The distance from the ray origin to the point.
 * @return The T_VECTOR point at distance T along RAY, computed as
 * origin + t * direction.
 * @note The direction vector of the ray should be normalized.
 */
t_vector	ray_point_at(t_ray ray, double t);

/**
 * Transforms a ray by applying a transformation matrix to it.
 * @param ray The ray to transform.
 * @param transform The T_MAT4 transformation matrix to apply.
 * @return The transformed T_RAY with both origin and direction updated.
 */
t_ray		ray_transform(t_ray ray, t_mat4 transform);

/*--------------------------------------------------------------------------*/
/*---------------------------------UTILITIES--------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Multiplies a 4x4 matrix by a vector treated as a point (w = 1).
 * @param v The vector to transform, treated as a point.
 * @param m The T_MAT4 transformation matrix.
 * @return The transformed T_VECTOR including translation effects.
 * @note Use this for transforming positions in homogeneous coordinates.
 */
t_vector	vector_mult_mat4_point(t_vector v, t_mat4 m);

/**
 * Multiplies a 4x4 matrix by a vector treated as a direction (w = 0).
 * @param v The vector to transform, treated as a direction.
 * @param m The T_MAT4 transformation matrix.
 * @return The transformed T_VECTOR unaffected by translation.
 * @note Use this for transforming normals and ray directions.
 */
t_vector	vector_mult_mat4_dir(t_vector v, t_mat4 m);

/**
 * Solves a quadratic equation of the form ax² + bx + c = 0.
 * @param a The coefficient of x².
 * @param b The coefficient of x.
 * @param c The constant term.
 * @return A T_ROOTS with has_solutions set to 1 and sol1 <= sol2 if real
 * solutions exist, or has_solutions set to 0 if no real solutions exist.
 * @note If the equation has a repeated root, sol1 and sol2 are equal.
 */
t_roots		solve_quadratic(double a, double b, double c);

/**
 * Converts a normalized color vector to a packed uint32_t pixel value.
 * @param color The T_VECTOR with r, g, b components in the 0.0-1.0 range.
 * @return A UINT32_T packed as 0x00RRGGBB ready for mlx buffer writing.
 * @note Components are clamped to 0.0-1.0 before conversion to prevent
 * overflow from lighting calculations that exceed the valid range.
 */
uint32_t	translate_color(t_vector color);

t_vector	color_hadamard(t_vector ca, t_vector cb);

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif