/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtelm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:20:30 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/20 18:23:39 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTELM_H
# define RTELM_H

# include "rtmlx.h"
# include "rtmth.h"
# include "libft.h"

/*--------------------------------------------------------------------------*/
/*--------------------------------STRUCTURES--------------------------------*/
/*--------------------------------------------------------------------------*/

# if BONUS
#  include "rtelm_bonus.h"
# else
/**
 * Represents a point light source in the scene.
 */
typedef struct s_elem_light_p
{
	t_vector	pos;   // World space position of the point light.
	double		ratio; // Brightness intensity in the 0.0-1.0 range.
}	t_elem_light_p;

/**
 * Represents the surface material properties of an object.
 */
typedef struct s_material
{
	t_vector color; // Normalized RGB color in the 0.0-1.0 range.
}	t_material;
# endif

/**
 * Represents an ambient light source affecting the whole scene.
 */
typedef struct s_elem_light_a
{
	double		ratio; // Brightness intensity in the 0.0-1.0 range.
	t_vector	color; // Normalized RGB color in the 0.0-1.0 range.
}	t_elem_light_a;

/**
 * Represents the scene camera and its precomputed viewport basis.
 */
typedef struct s_elem_camera
{
	t_vector	pos;    // World space position of the camera.
	t_vector	normal; // Forward facing direction of the camera.
	t_vector	up;     // Up basis vector scaled to viewport height.
	t_vector	right;  // Right basis vector scaled to viewport width.
	int			fov;    // Horizontal field of view angle in degrees.
	t_ray		(*get_pixel_ray)(void *ptr, int x, int y); // Ray generator.
}	t_elem_camera;

/**
 * Holds the precomputed inverse matrices of an object's transformation.
 * @note inv_transpose is used for correct normal transformation during
 * lighting calculations.
 */
typedef struct s_transform
{
	t_mat4	inv;           // Inverse transformation matrix M⁻¹.
	t_mat4	inv_transpose; // Transposed inverse (M⁻¹)ᵀ for normals.
}	t_transform;

/**
 * Represents a generic 3D object in the scene.
 * @note obj->data is NULL for planes since they have no unique geometry.
 * All intersection and normal calculations operate in local object space.
 */
typedef struct s_object
{
	t_transform	transform;  // Inverse and inverse transpose matrices.
	t_material	material;   // Surface material containing the color.
	void		*data;      // Object-specific geometry data.
	double		(*c_intersection)(t_ray local_ray); // Local intersection.
	t_vector	(*c_normal)(t_vector point);        // Local surface normal.
}	t_object;

/**
 * Holds the unique geometric properties of a cylinder.
 * @note Position and orientation are encoded in the transform matrix.
 */
typedef struct s_elem_cylinder
{
	double		diam;   // Diameter in world space units.
	double		height; // Height in world space units.
}	t_elem_cylinder;

/**
 * Holds the unique geometric properties of a sphere.
 * @note Position is encoded in the transform matrix.
 */
typedef struct s_elem_sphere
{
	double		diam; // Diameter in world space units.
}	t_elem_sphere;

/*--------------------------------------------------------------------------*/
/*---------------------------------BUILDERS---------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Initializes a camera from a parsed string array.
 * @param str The array of strings containing the camera parameters, where
 * str[1] is position, str[2] is normal, and str[3] is FOV.
 * @param camera A pointer to the T_ELEM_CAMERA to initialize.
 * @return 0 on success, 1 if the normal vector is zero.
 * @note Position, normal and FOV are parsed directly into the camera.
 * The get_pixel_ray function pointer and basis vectors are built after
 * validation. The camera is ready to generate rays after this call.
 */
int				build_camera(char **str, t_elem_camera *camera);

/**
 * Initializes an ambient light from a parsed string array.
 * @param str The array of strings containing the ambient light parameters,
 * where str[1] is the brightness ratio and str[2] is the RGB color.
 * @return A T_ELEM_LIGHT_A with ratio and normalized color initialized.
 * @note Color is stored as a normalized 0.0-1.0 T_VECTOR via build_color.
 */
t_elem_light_a	build_la(char **str);

/**
 * Allocates and initializes a point light from a parsed string array.
 * @param str The array of strings containing the point light parameters,
 * where str[1] is position and str[2] is the brightness ratio.
 * @return A pointer to the newly allocated T_ELEM_LIGHT_P, or NULL on
 * allocation failure.
 * The caller is responsible for freeing the returned pointer.
 * @note The bonus version also stores a color as a normlized 0.0-1.0
 * T_VECTOR via build_color.
 */
t_elem_light_p	*build_lp(char **str);

/**
 * Initializes a plane object from a parsed string array.
 * @param str The array of strings containing the plane parameters, where
 * str[1] is position, str[2] is normal, and str[3] is the RGB color.
 * @param obj The T_OBJECT to initialize with plane data and functions.
 * @return 0 on success, 1 if the normal vector is zero.
 * @note The plane has no unique geometry so obj->data is set to NULL.
 * Position and normal are consumed into the transform matrices and not
 * stored after this call.
 */
int				build_pl(char **str, t_object *obj);

/**
 * Initializes a cylinder object from a parsed string array.
 * @param str The array of strings containing the cylinder parameters, where
 * str[1] is position, str[2] is normal, str[3] is diameter, str[4] is
 * height, and str[5] is the RGB color.
 * @param obj The T_OBJECT to initialize with cylinder data and functions.
 * @return 0 on success, 1 if the normal vector is zero or allocation fails.
 * @note Position and normal are consumed into the transform matrices and
 * not stored. The object is fully initialized with intersection, normal
 * and matrix data after this call.
 */
int				build_cy(char **str, t_object *obj);

/**
 * Initializes a sphere object from a parsed string array.
 * @param str The array of strings containing the sphere parameters, where
 * str[1] is position, str[2] is diameter, and str[3] is the RGB color.
 * @param obj The T_OBJECT to initialize with sphere data and functions.
 * @return 0 on success, 1 if allocation fails.
 * @note A sphere has no orientation so normal is zeroed before being
 * consumed into the transform matrix. Position and normal are discarded
 * after the matrix is built.
 */
int				build_sp(char **str, t_object *obj);

/**
 * Allocates and initializes a generic 3D object using a builder function.
 * @param arr The array of strings containing the object's parameters.
 * @param builder A function pointer to the object-specific builder, which
 * fills the object's data, material, and function pointers.
 * @return A pointer to the newly allocated T_OBJECT, or NULL on failure.
 * @note The caller is responsible for freeing the returned object. Returns
 * NULL both on allocation failure and if the builder reports an error.
 */
t_object		*build_object(char **arr, int (*builder)(char **, t_object *));

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif