/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtelm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:20:30 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/24 20:33:38 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTELM_H
# define RTELM_H

# include "rtmth.h"
# if BONUS
#  include "elements_bonus.h"
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

void	*new_sphere(char *str);

#endif