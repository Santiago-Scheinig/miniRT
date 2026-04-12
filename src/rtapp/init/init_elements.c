/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:23:52 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 20:45:14 by sscheini         ###   ########.fr       */
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
	return (RT_SUCCESS);
}

/**
 * Parses, builds and adds a geometric object to the app object list.
 * @param argv The array of strings containing the object parameters.
 * @param i The line number in the scene file, used for error logging.
 * @param builder The T_OBJECT_BUILD containing the parse and build
 * function pointers for this specific object type.
 * @param app The T_RTAPP instance to add the object into.
 * @return RT_SUCCESS on success, RT_FAILURE if parsing fails, allocation
 * of the object or list node fails, or the normal vector is zero.
 * @note On list node allocation failure, the object is freed before
 * returning to avoid memory leaks.
 */
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
