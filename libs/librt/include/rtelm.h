/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtelm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:20:30 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/11 21:24:10 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTELM_H
# define RTELM_H

# include "rtmlx.h"
# include "rtmth.h"
# include "libft.h"
# if BONUS
#  include "rtelm_bonus.h"
# else

typedef struct s_elem_light_p
{
	t_vector	pos;
	double		ratio;
}	t_elem_light_p;

//We can add more information here later for the bonus
typedef struct s_material
{
	int rgb;
}	t_material;

# endif

//We can erase everything, a plane object doesnt need to have data, 
//only its matrixes, though we could save a flag. It is redundant;
typedef struct s_elem_plane
{
	t_vector	pos;
	t_vector	normal;
	int			rgb;
}	t_elem_plane;

//We can save only diam and height which are the main information that defines
//the object, both pos and normal are used to calculate the matrixes
typedef struct s_elem_cylinder
{
	t_vector	pos;
	t_vector	normal;
	double		diam;
	double		height;
	int			rgb;
}	t_elem_cylinder;

//We can save only diam, pos is used to calculate the matrixes
typedef struct s_elem_sphere
{
	t_vector	pos;
	double		diam;
	int			rgb;
}	t_elem_sphere;

typedef struct s_elem_camera
{
	t_vector	pos;
	t_vector	normal;
	int			fov;
	t_vector	right;
	t_vector	up;
	t_ray		(*get_pixel_ray)(void *ptr, int x, int y);
}	t_elem_camera;

typedef struct s_elem_light_a
{
	double		ratio;
	int			rgb;
}	t_elem_light_a;

typedef struct s_transform
{
	t_mat4	inv;
	t_mat4	inv_transpose;
}	t_transform;

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
	t_transform	transform;
	t_material	material;		
	void		*data;
	double		(*c_intersection)(t_ray local_ray);
	t_vector	(*c_normal)(t_vector point);
}	t_object;

t_elem_camera	new_camera(char **str);

t_elem_light_a	new_ambient_light(char **str);

t_elem_light_p	*new_light(char **str);

t_object		*new_plane(char **str);

t_object		*new_cylinder(char **str);

t_object		*new_sphere(char **str);

t_mat4			plane_inverse_mat4(t_object *obj);

t_mat4			cylinder_inverse_mat4(t_object *obj);

t_mat4			sphere_inverse_mat4(t_object *obj);

void			build_matrixes(t_object *new, t_mat4 (*inv_mtx)(t_object *));

#endif