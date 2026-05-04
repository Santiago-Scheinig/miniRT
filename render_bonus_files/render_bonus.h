/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:19:44 by aramos-r          #+#    #+#             */
/*   Updated: 2026/05/04 22:03:22 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H
# include "rtapp.h"
# include "rtapp_render.h"

typedef struct s_elem_cone
{
	t_vector	origin;
	t_vector	normal;
	double		diam;
	double		height;
}	t_elem_cone;

typedef struct s_elem_parabole
{
	t_vector	origin;
	t_vector	normal;
	double		diam;
	double		height;
}	t_elem_parabole;

typedef struct s_elem_hyperboloid
{
	t_vector	origin;
	t_vector	normal;
	double		diam;
	double		height;
}	t_elem_hyperboloid;

typedef struct s_elem_light_p
{
	t_vector	pos;
	double		ratio;
	t_vector	color;
}	t_elem_light_p;

typedef struct s_material
{
	t_vector	color;
	double		shininess;
}	t_material;

/**
 * @brief Computes the color at a ray-object intersection point using the
 * full Phong reflection model (ambient + diffuse + specular).
 * @param hit The T_HIT containing the intersection information for shading.
 * @param objects The list of T_OBJECTs in the scene for shadow ray testing.
 * @param app The T_RTAPP containing the scene's ambient light and point lights.
 * @return A T_VECTOR representing the final RGB color at the hit point, with
 * each component normalized to the 0.0-1.0 range.
 */
t_vector		get_color_at_hit(
					t_hit hit,
					t_list *objs,
					t_rtapp *app
					);

/**
 * @brief Computes the inverse transformation matrix for a cone.
 * @param obj Pointer to the cone object containing the cone data.
 * @param pos The position vector (center) of the cone in world space.
 * @param normal The normalized axis vector of the cone.
 * @return The inverse transformation matrix that converts world space
 *         coordinates to the cone's local object space (canonical form).
 * @note Constructs a 4x4 transformation matrix that combines translation,
 *       rotation, and scaling to position the cone in world space, then
 *       inverts it to enable ray-cone intersection calculations in local
 *       coordinates.
 */
t_mat4		cn_inv_mat4(t_object *obj, t_vector pos, t_vector normal);

/**
 * @brief Computes the surface normal at a point on the cone.
 * @param local_point A point in the cone's local object space.
 * @return The normalized surface normal vector at the given point.
 * @note For points on the top cap (Y >= 1.0), returns the cap normal
 *       (0, 1, 0). For points on the cone's sides, computes the normal
 *       vector based on the cone's implicit equation and normalizes it.
 */
t_vector	cn_normal(t_vector local_point);

/**
 * @brief Computes the ray-cone intersection distance.
 * @param local_ray A ray in the cone's local object space.
 * @return The distance T along the ray to the closest intersection point.
 *         Returns INFINITY if no intersection exists.
 * @note The cone is treated as a finite object with bounds
 *       0.0 <= Y <= 1.0. The function checks both the cone's side
 *       surface and its top cap, returning the smallest positive
 *       distance for correct depth ordering.
 */
double		cn_intersection(t_ray local_ray);

/**
 * @brief Computes the inverse transformation matrix for a paraboloid.
 * @param obj Pointer to the paraboloid object containing the paraboloid data.
 * @param pos The position vector (vertex) of the paraboloid in world space.
 * @param normal The normalized axis vector of the paraboloid.
 * @return The inverse transformation matrix that converts world space
 *         coordinates to the paraboloid's local object space (canonical form).
 * @note Constructs a 4x4 transformation matrix that combines translation,
 *       rotation, and scaling to position the paraboloid in world space, then
 *       inverts it to enable ray-paraboloid intersection calculations in local
 *       coordinates.
 */
t_mat4		pb_inv_mat4(t_object *obj, t_vector pos, t_vector normal);

/**
 * @brief Computes the surface normal at a point on the paraboloid.
 * @param local_point A point in the paraboloid's local object space.
 * @return The normalized surface normal vector at the given point.
 * @note For points on the top cap (Y >= 1.0), returns the cap normal
 *       (0, 1, 0). For points on the paraboloid's sides, computes the normal
 *       vector based on the paraboloid's implicit equation x² + z² - y = 0
 *       and normalizes it.
 */
t_vector	pb_normal(t_vector local_point);

/**
 * @brief Computes the ray-paraboloid intersection distance.
 * @param local_ray A ray in the paraboloid's local object space.
 * @return The distance T along the ray to the closest intersection point.
 *         Returns INFINITY if no intersection exists.
 * @note The paraboloid is treated as a finite object with bounds
 *       0.0 <= Y <= 1.0. The function checks both the paraboloid's side
 *       surface and its open top cap, returning the smallest positive
 *       distance for correct depth ordering.
 */
double		pb_intersection(t_ray local_ray);

/**
 * @brief Computes the inverse transformation matrix for a hyperboloid.
 * @param obj Pointer to the hyperboloid object containing the hyperboloid data.
 * @param pos The position vector (center) of the hyperboloid in world space.
 * @param normal The normalized axis vector of the hyperboloid.
 * @return The inverse transformation matrix that converts world space
 *         coordinates to the hyperboloid's local object space (canonical form).
 * @note Constructs a 4x4 transformation matrix that combines translation,
 *       rotation, and scaling to position the hyperboloid in world space, then
 *       inverts it to enable ray-hyperboloid intersection calculations in local
 *       coordinates.
 */
t_mat4		hb_inv_mat4(t_object *obj, t_vector pos, t_vector normal);

/**
 * @brief Computes the surface normal at a point on the hyperboloid.
 * @param local_point A point in the hyperboloid's local object space.
 * @return The normalized surface normal vector at the given point.
 * @note Computes the normal vector based on the hyperboloid's implicit
 *       equation x² + z² - y² = 1 and normalizes it.
 */
t_vector	hb_normal(t_vector local_point);

/**
 * @brief Computes the ray-hyperboloid intersection distance.
 * @param local_ray A ray in the hyperboloid's local object space.
 * @return The distance T along the ray to the closest intersection point.
 *         Returns INFINITY if no intersection exists.
 * @note The hyperboloid is treated as a finite object with bounds
 *       -1.0 <= Y <= 1.0. The surface is hollow (no caps), only the
 *       side surface is checked for intersections.
 */
double		hb_intersection(t_ray local_ray);

#endif