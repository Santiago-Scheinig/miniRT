/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:19:44 by aramos-r          #+#    #+#             */
/*   Updated: 2026/05/10 17:44:28 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H
# include "rtapp.h"
# include "rtapp_render.h"
# include <pthread.h>
# define WORKER_COUNT 16

/**
 * Represents the full state of the miniRT application.
 * @note objects and lights are NULL until parsed from the scene file.
 * camera.get_pixel_ray being NULL indicates the camera is uninitialized.
 * ambient.ratio being -1 indicates the ambient light is uninitialized.
 */
typedef struct s_rtapp
{
	uint32_t		*img; // Render buffer for img, allocated after parsing.
	t_list			*objects;	// Linked list of T_OBJECT scene elements.
	t_list			*lights;	// Linked list of T_ELEM_LIGHT_P point lights.
	t_elem_camera	camera;		// Unique camera instance for the scene.
	t_elem_light_a	ambient;	// Unique ambient light instance for the scene.
	t_tile_queue	tile_queue;	// Queue of tiles to render.
	pthread_t		workers[WORKER_COUNT]; // Array of worker threads.
	pthread_mutex_t	queue_mutex; // Mutex to protect tile queue access.
}	t_rtapp;

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

/**
 * @brief Maps a sphere's local point to UV coordinates.
 * @param local_point The point in the sphere's local object space.
 * @return A T_UV with U = atan2(z,x)/(2π) + 0.5 and V = asin(y)/π + 0.5.
 */
t_uv		sphere_uv(t_vector local_point);

/**
 * @brief Maps a cylinder's local point to UV coordinates.
 * @param local_point The point in the cylinder's local object space.
 * @return A T_UV with U = atan2(z,x)/(2π) + 0.5 and V = (y+1)/2.
 */
t_uv		cylinder_uv(t_vector local_point);

/**
 * @brief Maps a cone's local point to UV coordinates.
 * @param local_point The point in the cone's local object space.
 * @return A T_UV with U = atan2(z,x)/(2π) + 0.5 and V = y.
 */
t_uv		cone_uv(t_vector local_point);

/**
 * @brief Maps a plane's local point to UV coordinates.
 * @param local_point The point in the plane's local object space.
 * @return A T_UV with U = x and V = z.
 */
t_uv		plane_uv(t_vector local_point);

/**
 * @brief Maps a paraboloid's local point to UV coordinates.
 * @param local_point The point in the paraboloid's local object space.
 * @return A T_UV with U = atan2(z,x)/(2π) + 0.5 and V = y.
 */
t_uv		paraboloid_uv(t_vector local_point);

/**
 * @brief Maps a hyperboloid's local point to UV coordinates.
 * @param local_point The point in the hyperboloid's local object space.
 * @return A T_UV with U = atan2(z,x)/(2π) + 0.5 and V = (y+1)/2.
 */
t_uv		hyperboloid_uv(t_vector local_point);

/**
 * @brief Computes the checkerboard color at a given UV coordinate.
 * @param uv The UV coordinates on the checkerboard surface.
 * @return A T_VECTOR of (1,1,1) for white squares or (0,0,0) for black
 *         squares, based on a checkerboard scale of CHECKER_SCALE.
 */
t_vector	get_checker_color(t_uv uv);

/**
 * @brief Loads a normal map image from file.
 * @param filepath Path to the image file (PNG, JPG, BMP, TGA, etc.).
 * @return A pointer to a newly allocated T_NORMAL_MAP, or NULL on failure.
 * @note The caller is responsible for freeing the returned struct and its
 *       pixels array.
 */
t_normal_map	*load_normal_map(char *filepath);

/**
 * @brief Frees a normal map structure and its pixel data.
 * @param nmap Pointer to the normal map to free.
 */
void			free_normal_map(t_normal_map *nmap);

/**
 * @brief Computes a perturbed normal from a normal map at a hit point.
 * @param hit The hit information containing the surface normal.
 * @param local_point The intersection point in the object's local space.
 * @return The perturbed normal in world space, or the original surface
 *         normal if no normal map or tangent function is available.
 */
t_vector		get_perturbed_normal(t_hit hit, t_vector local_point);

/**
 * @brief Computes the tangent vector for a plane in local space.
 * @param local_point The point on the plane in local space.
 * @return The tangent vector (1, 0, 0).
 */
t_vector		plane_tangent(t_vector local_point);

/**
 * @brief Computes the tangent vector for a sphere in local space.
 * @param local_point The point on the sphere in local space.
 * @return The normalized tangent vector perpendicular to the surface normal.
 */
t_vector		sphere_tangent(t_vector local_point);

/**
 * @brief Computes the tangent vector for a cylinder in local space.
 * @param local_point The point on the cylinder in local space.
 * @return The normalized tangent vector perpendicular to the surface normal.
 */
t_vector		cylinder_tangent(t_vector local_point);

/**
 * @brief Computes the tangent vector for a cone in local space.
 * @param local_point The point on the cone in local space.
 * @return The normalized tangent vector perpendicular to the surface normal.
 */
t_vector		cone_tangent(t_vector local_point);

/**
 * @brief Computes the tangent vector for a paraboloid in local space.
 * @param local_point The point on the paraboloid in local space.
 * @return The normalized tangent vector perpendicular to the surface normal.
 */
t_vector		paraboloid_tangent(t_vector local_point);

/**
 * @brief Computes the tangent vector for a hyperboloid in local space.
 * @param local_point The point on the hyperboloid in local space.
 * @return The normalized tangent vector perpendicular to the surface normal.
 */
t_vector		hyperboloid_tangent(t_vector local_point);

#endif