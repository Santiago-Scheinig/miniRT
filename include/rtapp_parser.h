/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:43:31 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 17:21:46 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_PARSER_H
# define RTAPP_PARSER_H

# include "rtapp.h"
# include <float.h>

extern const char	*g_la_msgs[];
extern const char	*g_lp_msgs[];
extern const char	*g_ca_msgs[];
extern const char	*g_pl_msgs[];
extern const char	*g_cy_msgs[];
extern const char	*g_sp_msgs[];

typedef struct s_dlim
{
	double	min;
	double	max;
}	t_dlim;

int				parse_arg(char **arr, int i, const char **msgs, int expected);

int				parse_line(t_list *line, int i, t_rtapp *app);

int				parse_vector(char *sp, char *str, int i, t_dlim limits);

int				parse_double(char *sp, char *str, int i, t_dlim limits);

int				parse_camera(char **split, int i);

int				parse_lp(char **split, int i);

int				parse_pl(char **split, int i);

int				parse_cy(char **split, int i);

int				parse_sp(char **split, int i);

int				parse_la(char **split, int i);

#endif