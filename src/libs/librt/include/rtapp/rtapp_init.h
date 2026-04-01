/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_init.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:10:37 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/27 17:04:54 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"

t_list		*init_file(char *file);

int			init_log(t_rtapp *app);

int			init_objlst(t_list *lines, char *file, t_rtapp *app);

int			init_plane(char **argv, int i, t_rtapp *app);

int			init_cylinder(char **argv, int i, t_rtapp *app);

int			init_sphere(char **argv, int i, t_rtapp *app);

int			init_light(char **argv, int i, t_rtapp *app);

int			init_camera(char **argv, int i, t_rtapp *app);

int			init_ambient_light(char **argv, int i, t_rtapp *app);

t_object	*new_obj(char **split, t_object *(*constructor)(char **));
