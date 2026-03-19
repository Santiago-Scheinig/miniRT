/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:25:16 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/19 18:44:50 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * OBJECTS_BONUS.h
 */

typedef enum e_elements
{
	PLANE,
	CYLINDER,
	SPHERE,
	FIGURA1,
	FIGURA2,
	FIGURA3,
	etc..
}	t_elements;

typedef struct s_elem_light_p
{
	t_vector	pos;
	float		ratio;
	int			rgb
}	t_elem_light_p;

bump
cone
hyperboloid
paraboloid
etc
etc