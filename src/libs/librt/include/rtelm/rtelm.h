/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtelm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:20:30 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 19:38:25 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTELM_H
# define RTELM_H

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
}	t_elem_camera;

typedef struct s_elem_light_a
{
	float		ratio;
	int			rgb;
}	t_elem_light_a;

typedef struct s_object
{
	void		*data;
	void		*(*intersection)(void *);
	void		*(*normal)(void *);
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

#endif