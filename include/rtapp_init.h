/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_init.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:10:37 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 18:12:57 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_INIT_H
# define RTAPP_INIT_H

# include "rtapp.h"

typedef struct s_object_build
{
	int	(*parse)(char **arr, int i);
	int (*build)(char **arr, t_object *obj);
	int (*info)(t_object *obj);
}	t_object_build;

typedef struct s_dispatch
{
	const char	*specifier;
	int			(*initializer)(char **, int, t_rtapp *);
}	t_dispatch;

typedef struct s_obj_dispatch
{
    const char      *specifier;
    t_object_build  builder;
}   t_obj_dispatch;

extern const t_obj_dispatch g_obj_dispatch[];

extern const t_dispatch g_dispatch[];

int			init_log(t_rtapp *app);

t_list		*init_file(char *file);

int			init_file_contents(t_list *lines, char *file, t_rtapp *app);

int			init_camera(char **argv, int i, t_rtapp *app);

int			init_light_a(char **argv, int i, t_rtapp *app);

int			init_light_p(char **argv, int i, t_rtapp *app);

int			init_object(char **argv, int i, t_rtapp *app);

#endif