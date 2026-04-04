/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtelm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:20:30 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/04 12:04:27 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTELM_H
# define RTELM_H
# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1920
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 1080
# endif

# include "rtmth.h"
# include "libft.h"
# if BONUS
#  include "rtelm_bonus.h"
# else

typedef enum e_elements
{
	INV = -1,
	PL,
	CY,
	SP,
}	t_elements;

typedef struct s_elem_light_p
{
	t_vector	pos;
	float		ratio;
}	t_elem_light_p;

# endif

typedef struct s_elem_plane
{
	t_vector	pos;
	t_vector	normal;
	int			rgb;
}	t_elem_plane;

typedef struct s_elem_cylinder
{
	t_vector	pos;
	t_vector	normal;
	float		diam;
	float		height;
	int			rgb;
}	t_elem_cylinder;

typedef struct s_elem_sphere
{
	t_vector	pos;
	float		diam;
	int			rgb;
}	t_elem_sphere;

typedef struct s_elem_camera
{
	t_vector	pos;
	t_vector	normal;
	int			fov;
	t_vector	right;
	t_vector	up;
}	t_elem_camera;

typedef struct s_elem_light_a
{
	float		ratio;
	int			rgb;
}	t_elem_light_a;

/**
 * @brief Structure to represent a generic 3D object in the ray tracer.
 * @param data A pointer to the specific data structure for the object type
 * (e.g., t_elem_plane, t_elem_sphere, t_elem_cylinder).
 * @param inverse The inverse transformation matrix for the object, used to
 * transform rays into the object's local space for intersection calculations.
 * @param transposed_inv The transposed inverse transformation matrix, used for
 * transforming normals correctly when calculating lighting.
 * @param intersection A function pointer to the intersection function for the
 * object, which takes a ray in the object's local space and it's data
 *  and returns the distance
 * to the closest intersection point, or INFINITY if there is no intersection.
 * @param get_normal A function pointer to the normal calculation function for
 * the object, which takes a point on the object's surface and its data,
 * and returns the normal vector at that point.
 * @note The specific data structure pointed to by data should be cast to the
 * appropriate type (e.g., t_elem_plane *) when used in the intersection and
 * get_normal functions.
 * @warning The ray passed to the intersection function must
 * be in the object's local space,
 * which typically means it should be transformed using the inverse matrix
 * before calling the intersection function.
 */
typedef struct s_object
{
	void		*data;
	t_mat4		inverse;
	t_mat4		transposed_inv;
	double		(*intersection)(t_ray local_ray, void *data);
	t_vector	(*get_normal)(t_vector point, void *data);
}	t_object;

t_elem_camera	new_camera(char **str);

t_elem_light_a	new_ambient_light(char **str);

t_elem_light_p	*new_light(char **str);

t_object		*new_plane(char **str);

t_object		*new_cylinder(char **str);

t_object		*new_sphere(char **str);

/**
 * @brief Gets the inverse transformation matrix for a plane given
 * a point and normal.
 * @param point A point on the plane.
 * @param normal The normal vector of the plane.
 * @return The inverse transformation matrix.
 */
t_mat4			plane_get_inverse_mat4(t_vector point, t_vector normal);

/**
 * @brief Gets the inverse transformation matrix for a sphere given
 * its center and diameter.
 * @param center The center of the sphere.
 * @param diameter The diameter of the sphere.
 * @return The inverse transformation matrix.
 */
t_mat4			sphere_get_inverse_mat4(t_vector center, double diameter);

/**
 * @brief Gets the inverse transformation matrix for a cylinder given
 * its center, diameter, normal vector, and height.
 * @param center The center of the cylinder.
 * @param diameter The diameter of the cylinder.
 * @param normal The normal vector of the cylinder.
 * @param height The height of the cylinder.
 * @return The inverse transformation matrix.
 */
t_mat4			cylinder_get_inverse_mat4(t_vector center,
					double diameter,
					t_vector normal,
					double height);

/**
 * @brief Calculates the distance of the closest
 * intersection of a ray with a plane.
 * @param ray The ray to test for intersection.
 * @param data A pointer to the plane data (t_elem_plane *).
 * @return The distance to the closest intersection point,
 * or INFINITY if there is no intersection.
 * @note INFINITY is greater than any finite distance,
 * so it can be used to indicate no intersection.
 */
double			plane_intersection(t_ray ray, void *data);

/**
 * @brief Calculates the distance of the closest
 * intersection of a ray with a sphere.
 * @param ray The ray to test for intersection.
 * @param data A pointer to the sphere data (t_elem_sphere *).
 * @return The distance to the closest intersection point,
 * or INFINITY if there is no intersection.
 */
double			sphere_intersection(t_ray ray, void *data);

/**
 * @brief Calculates the distance of the closest
 * valid intersection of a ray with a cylinder.
 * @param ray The ray to test for intersection.
 * @param data A pointer to the cylinder data (t_elem_cylinder *).
 * @return The distance to the closest intersection point,
 * or INFINITY if there is no intersection or it's invalid (e.g negative).
 */
double			cylinder_intersection(t_ray ray, void *data);

/**
 * @brief Calculates the local normal vector
 * at a given local point on a plane.
 * @param local_point The point on the plane in local coordinates.
 * @param data A pointer to the plane data (t_elem_plane *).
 * @return The local normal vector at the specified point.
 * @note This vector is in local coordinates and should be
 * transformed to global and then nomalized before use.
 */
t_vector		plane_get_normal(t_vector local_point, void *data);

/**
 * @brief Calculates the local normal vector
 * at a given local point on a sphere.
 * @param local_point The point on the sphere in local coordinates.
 * @param data A pointer to the sphere data (t_elem_sphere *).
 * @return The local normal vector at the specified point.
 * @note This vector is in local coordinates and should be
 * transformed to global and then nomalized before use.
 */
t_vector		sphere_get_normal(t_vector local_point, void *data);

/**
 * @brief Calculates the local normal vector
 * at a given local point on a cylinder.
 * @param local_point The point on the cylinder in local coordinates.
 * @param data A pointer to the cylinder data (t_elem_cylinder *).
 * @return The local normal vector at the specified point.
 * @note This vector is in local coordinates and should be
 * transformed to global and then nomalized before use.
 */
t_vector		cylinder_get_normal(t_vector local_point, void *data);

/**
 * @brief Generates a ray from the camera
 * through a specific pixel on the screen.
 * @param camera The camera element containing the
 * position, normal, and field of view.
 * @param x The x-coordinate of the pixel on the screen.
 * @param y The y-coordinate of the pixel on the screen.
 * @return A global ray originating from the camera and passing
 * through the specified pixel.
 */
t_ray			get_pixel_ray(t_elem_camera *camera, int x, int y);

#endif