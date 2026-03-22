/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_init.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:10:37 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/22 20:31:07 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elements.h"
#include "rterr.h"
#include "libft.h"
#include <fcntl.h>

typedef struct s_rtapp
{
	t_list			*objects;
	t_list			*lights;
	t_elem_camera	camera;
	t_elem_light_a	ambient;
	t_rtlog			logfd;
}	t_rtapp;

t_list	*parser(char *file);

int		init_log(t_rtapp *app);
