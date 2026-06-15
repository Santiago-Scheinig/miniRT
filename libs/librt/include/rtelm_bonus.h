/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtelm_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 16:47:35 by sscheini          #+#    #+#             */
/*   Updated: 2026/06/15 16:10:52 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTELM_BONUS_H
# define RTELM_BONUS_H

# include "libft.h"
# include "rtmth.h"
# include "rtmlx.h"
# include <fcntl.h>
# include <stdint.h>
# include <sys/stat.h>

/**
 * Represents a point light source in the scene.
 */
typedef struct s_elem_light_p
{
	double		ratio;	// Brightness intensity in the 0.0-1.0 range.
	t_vector	pos;	// World space position of the point light.
	t_vector	color;
}	t_elem_light_p;

typedef struct s_texture
{
	void		*img;
	uint32_t	*pixels;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}	t_texture;

typedef struct s_phong
{
	t_vector	color;
	double		exponent;
}	t_phong;

typedef struct s_material
{
	t_texture		map;
	t_vector		color;
	t_phong			specular;
	int				is_checker;
}	t_material;

/**
 * Holds the precomputed inverse matrices of an object's transformation.
 * @note inv_transpose is used for correct normal transformation during
 * lighting calculations.
 */
typedef struct s_transform
{
	t_mat4	mat;
	t_mat4	inv;			// Inverse transformation matrix M⁻¹.
	t_mat4	inv_transpose;	// Transposed inverse (M⁻¹)ᵀ for normals.
}	t_transform;

typedef struct s_object
{
	t_mlx		*mlx;
	t_transform	transform;
	t_material	material;
	void		*data;
	double		(*c_intersection)(t_ray local_ray);
	t_vector	(*c_normal)(t_vector point);
	t_vector	(*c_tangent)(t_vector local_point);
	t_uv		(*c_uv_map)(t_vector local_point);
}	t_object;

int	build_cn(char **str, t_object *obj);

int	build_hb(char **str, t_object *obj);

int	build_pb(char **str, t_object *obj);

#endif