/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:38:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 16:40:06 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_H
# define RTAPP_H

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# include "libft.h"
# include "rtelm.h"
# include "rterr.h"
# include "rtmlx.h"
# include "rtmth.h"
# if BONUS
#  include "rtapp_bonus.h"
# endif

typedef struct s_rtapp
{
	t_list			*objects;
	t_list			*lights;
	t_elem_camera	camera;
	t_elem_light_a	ambient;
	t_rtlog			logfd;
}	t_rtapp;

int	rtapp_init(int argc, char **argv, t_rtapp *app);

int rtapp_kill(t_rtapp *app, t_rterr errcode);

#endif