/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:23:52 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 18:11:27 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"
#include "rtapp_parser.h"

int	init_light_a(char **argv, int i, t_rtapp *app)
{
	const char	*err = "[line: %i][%s] initialization failed: %s";

	if (app->ambient.ratio != -1)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], "already defined."));
	if (parse_la(argv, i))
		return (RT_FAILURE);
	app->ambient = build_la(argv);

/* 	rtlog(RT_LOG, 0, "[line: %i] ratio:\t\t%f", i, app->ambient.ratio);
	rtlog(RT_LOG, 0, "[line: %i] colour:\t\t%i", i, app->ambient.rgb); */

	return (RT_SUCCESS);
}

int init_light_p(char **argv, int i, t_rtapp *app)
{
	const char		*err = "[line: %i][%s] initialization failed: %s";
	t_elem_light_p	*new_light_p;
	t_list			*new_node;

	if (app->lights)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], "already defined."));
	if (parse_lp(argv, i))
		return (RT_FAILURE);
	new_light_p = build_lp(argv);
	if (!new_light_p)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
	new_node = ft_lstnew(new_light_p);
	if (!new_node)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
	ft_lstadd_back(&(app->lights), new_node);

/* 	rtlog(RT_LOG, 0, "[line: %i] position:\t%f,%f,%f", i, new_light_p->pos.x, new_light_p->pos.y, new_light_p->pos.z);
	rtlog(RT_LOG, 0, "[line: %i] ratio:\t\t%f", i, new_light_p->ratio); */

	return (RT_SUCCESS);
}

int init_camera(char **argv, int i, t_rtapp *app)
{
	const char	*err = "[line: %i][%s] initialization failed: %s";

	if (app->camera.get_pixel_ray)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], "already defined."));
	if (parse_camera(argv, i))
		return (RT_FAILURE);
	if (build_camera(argv, &(app->camera)))
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], "invalid normal."));

/* 	rtlog(RT_LOG, 0, "[line: %i] position:\t%f,%f,%f", i, app->camera.pos.x, app->camera.pos.y, app->camera.pos.z);
	rtlog(RT_LOG, 0, "[line: %i] normal:\t\t%f,%f,%f", i, app->camera.normal.x, app->camera.normal.y, app->camera.normal.z);
	rtlog(RT_LOG, 0, "[line: %i] FOV:\t\t%i", i, app->camera.fov); */

	return (RT_SUCCESS);
}

static int	build_and_add(char **argv, int i, t_object_build builder, t_rtapp *app)
{
	const char		*err = "[line: %i][%s] initialization failed: %s";
	t_object		*obj;
	t_list			*new_node;
	
	if (builder.parse(argv, i))
		return (RT_FAILURE);
	obj = build_object(argv, builder.build);
	if (!obj)
	{
		if (errno)
			return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], "invalid normal."));
	}			
	new_node = ft_lstnew(obj);
	if (!new_node)
	{
		object_del(obj);
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
	}
	ft_lstadd_back(&(app->objects), new_node);
	//print_obj_info(obj, builder.print_info);
	return (RT_SUCCESS);
}

int	init_object(char **arr, int i, t_rtapp *app)
{
    const char  *err = "[line: %i][%s] initialization failed: %s";
    int         j;

    j = 0;
    while (g_obj_dispatch[j].specifier)
    {
        if (!ft_strncmp(arr[0], g_obj_dispatch[j].specifier,
                ft_strlen(g_obj_dispatch[j].specifier) + 1))
            return (build_and_add(arr, i, g_obj_dispatch[j].builder, app));
        j++;
    }
    return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid element."));
}
