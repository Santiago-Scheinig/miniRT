/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:38:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/24 16:57:52 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_H
# define RTAPP_H

# include "libft.h"
# include "rtelm.h"
# include "rterr.h"
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