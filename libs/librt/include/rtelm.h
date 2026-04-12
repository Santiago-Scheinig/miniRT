/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtelm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:20:30 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 19:10:42 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTELM_H
# define RTELM_H

# include "rtmlx.h"
# include "rtmth.h"
# include "libft.h"
# include <stdint.h>
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
	t_vector color;
}	t_material;

# endif

typedef struct s_elem_cylinder
{
	double		diam;
	double		height;
}	t_elem_cylinder;

typedef struct s_elem_sphere
{
	double		diam;
}	t_elem_sphere;

typedef struct s_elem_camera
{
	t_vector	pos;
	t_vector	normal;
	t_vector	up;
	t_vector	right;
	int			fov;

	t_ray		(*get_pixel_ray)(void *ptr, int x, int y);
}	t_elem_camera;

typedef struct s_elem_light_a
{
	double		ratio;
	t_vector	color;
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
	//Object Data
	t_transform	transform;
	t_material	material;		
	void		*data;
	
	//Object Member Funcitons
	double		(*c_intersection)(t_ray local_ray);
	t_vector	(*c_normal)(t_vector point);
}	t_object;

int				build_camera(char **str, t_elem_camera *camera);

t_elem_light_a	build_la(char **str);

t_elem_light_p	*build_lp(char **str);

int				build_pl(char **str, t_object *obj);

int				build_cy(char **str, t_object *obj);

int				build_sp(char **str, t_object *obj);

t_object		*build_object(char **arr, int (*builder)(char **, t_object *));

uint32_t		translate_color(t_vector color);

#endif