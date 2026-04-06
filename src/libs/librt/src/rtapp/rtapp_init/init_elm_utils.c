/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elm_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:42:30 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 17:39:16 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"
#include "rtapp_parser.h"

int init_light(char **argv, int i, t_rtapp *app)
{
	const char		*errmsg = "Failed to initialize %s: %s";
	t_elem_light_p	*new_light_p;
	t_list			*new_node;

	if (parse_light(argv, i))
		return (RT_FAILURE);
	new_light_p = new_light(argv);
	if (!new_light_p)
		return (rtlog(RT_ERRLOG, 0, errmsg, argv[0], strerror(errno)));
	new_node = ft_lstnew(new_light_p);
	if (!new_node)
		return (rtlog(RT_ERRLOG, 0, errmsg, argv[0], strerror(errno)));
	ft_lstadd_back(&(app->lights), new_node);
	return (RT_SUCCESS);
}

int	init_ambient_light(char **argv, int i, t_rtapp *app)
{
	const char	*errmsg = "Parser error for %s in line %i: %s";

	if (app->ambient.ratio != -1)
		return (rtlog(RT_ERRLOG, 0, errmsg, argv[0], i, "already defined."));
	if (parse_ambient_light(argv, i))
		return (RT_FAILURE);
	app->ambient = new_ambient_light(argv);
	return (RT_SUCCESS);
}

int init_camera(char **argv, int i, t_rtapp *app)
{
	const char	*errmsg = "Parser error for %s in line %i: %s";

	rtlog(RT_LOG, 0, "[%i] Initializing %s element.", i);
	if (app->camera.fov != -1)
		return (rtlog(RT_ERRLOG, 0, errmsg, argv[0], i, "already defined."));
	if (parse_camera(argv, i))
		return (RT_FAILURE);
	app->camera = new_camera(argv);
	rtlog(RT_LOG, 0, "[%i] %s element successfully initialized.", i, argv[0]);
	return (RT_SUCCESS);
}