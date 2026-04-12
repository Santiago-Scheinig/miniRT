/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_init.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:10:37 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 18:38:22 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_INIT_H
# define RTAPP_INIT_H

# include "rtapp.h"

t_list		*init_file(char *file);

int			init_log(t_rtapp *app);

int			init_objlst(t_list *lines, char *file, t_rtapp *app);

int			init_plane(char **argv, int i, t_rtapp *app);

int			init_cylinder(char **argv, int i, t_rtapp *app);

int			init_sphere(char **argv, int i, t_rtapp *app);

int			init_light(char **argv, int i, t_rtapp *app);

int			init_camera(char **argv, int i, t_rtapp *app);

int			init_ambient_light(char **argv, int i, t_rtapp *app);

#endif