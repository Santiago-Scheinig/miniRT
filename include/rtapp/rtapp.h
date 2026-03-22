/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:38:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/22 19:54:22 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "rtapp_init.h"
# include "rterr.h"
# include "rtmlx.h"
# include "rtmth.h"
# include "elements.h"
# if BONUS
#  include "rtapp_bonus.h"
# endif

typedef struct s_object
{
	t_elements	id;
	void		*obj;
//	void		(void *)(*fio)(void *);
}	t_object;

typedef struct s_rtapp
{
	t_list			*objects;
	t_list			*lights;
	t_elem_camera	camera;
	t_elem_light_a	ambient;
	t_rtlog			logfd;
}	t_rtapp;

int	rtapp_init(int argc, char **argv, t_rtapp *app);

int rtapp_kill(t_rtapp *app);

#endif