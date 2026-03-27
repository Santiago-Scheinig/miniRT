/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:43:31 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/27 16:56:25 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"
#include <float.h>

typedef struct s_flim
{
	float	min;
	float	max;
}	t_flim;

int				parse_line(t_list *line, int i, t_rtapp *app);

int				parse_vector(char *sp, char *str, int i, t_flim limits);

int				parse_float(char *sp, char *str, int i, t_flim limits);

int				parse_color(char *sp, char *str, int i);

int				parse_light(char **split, int i);

int 			parse_plane(char **split, int i);

int				parse_cylinder(char **split, int i);

int				parse_sphere(char **split, int i);

int				parse_ambient_light(char **split, int i);

int				parse_camera(char **split, int i);