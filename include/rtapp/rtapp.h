/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:38:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/19 18:15:41 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "rterr.h"
# include "rtmlx.h"
# include "rtmth.h"
# include "libft.h"
# include "elements.h"
# if BONUS
#  include "rtapp_bonus.h"
# endif

typedef struct s_object
{
	t_elements	id;
	void		*obj;
	void		(void *)(*fio)(void *);
}	t_object;

typedef struct s_rtapp
{
	t_list			*objects;
	t_list			*lights;
	t_elem_camera	camera;
	t_elem_light_a	ambient;
}	t_rtapp;

#endif