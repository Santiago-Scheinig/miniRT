/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elm_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:42:30 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 19:04:56 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"
#include "rtapp_parser.h"

int init_light(char **argv, int i, t_rtapp *app)
{
	const char		*err = "[line: %i] initialization of %s failed: %s";
	t_elem_light_p	*new_light_p;
	t_list			*new_node;

	if (parse_light(argv, i))
		return (RT_FAILURE);
	new_light_p = new_light(argv);
	if (!new_light_p)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
	new_node = ft_lstnew(new_light_p);
	if (!new_node)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
	ft_lstadd_back(&(app->lights), new_node);

	rtlog(RT_LOG, 0, "[line: %i] position:\t\t%f,%f,%f", i, new_light_p->pos.x, new_light_p->pos.y, new_light_p->pos.z);
	rtlog(RT_LOG, 0, "[line: %i] ratio:\t\t%f", i, new_light_p->ratio);

	return (RT_SUCCESS);
}

int	init_ambient_light(char **argv, int i, t_rtapp *app)
{
	const char	*err = "[line: %i] initialization of %s failed: %s";

	if (app->ambient.ratio != -1)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], "already defined."));
	if (parse_ambient_light(argv, i))
		return (RT_FAILURE);
	app->ambient = new_ambient_light(argv);

	rtlog(RT_LOG, 0, "[line: %i] ratio:\t\t%f", i, app->ambient.ratio);
	rtlog(RT_LOG, 0, "[line: %i] colour:\t\t%f", i, app->ambient.rgb);

	return (RT_SUCCESS);
}

int init_camera(char **argv, int i, t_rtapp *app)
{
	const char	*err = "[line: %i] initialization of %s failed: %s";

	if (app->camera.fov != -1)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], "already defined."));
	if (parse_camera(argv, i))
		return (RT_FAILURE);
	app->camera = new_camera(argv);

	rtlog(RT_LOG, 0, "[line: %i] position:\t%f,%f,%f", i, app->camera.pos.x, app->camera.pos.y, app->camera.pos.z);
	rtlog(RT_LOG, 0, "[line: %i] normal:\t\t%f,%f,%f", i, app->camera.normal.x, app->camera.normal.y, app->camera.normal.z);
	rtlog(RT_LOG, 0, "[line: %i] FOV:\t\t%i", i, app->camera.fov);

	return (RT_SUCCESS);
}