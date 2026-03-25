/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:40:22 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/25 21:25:06 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"

static int	obj_to_app(t_object *new_obj, t_rtapp *app)
{
	
}

static t_object	*parse_element(char **split, int i)
{
	if (!ft_strncmp(split[0], "pl", 3))
		return (parse_plane(split, i));
	if (!ft_strncmp(split[0], "cy", 3))
		return (parse_cylinder(split, i));
	if (!ft_strncmp(split[0], "sp", 3))
		return (parse_sphere(split, i));
	if (!ft_strncmp(split[0], "C", 2))
		return (parse_camera(split, i));
	if (!ft_strncmp(split[0], "L", 2))
		return (parse_light(split, i));
	if (!ft_strncmp(split[0], "A", 2))
		return (parse_ambience_light(split, i));
	rtlog(RT_ERRLOG, 0, "Failed to parse line %i: %s", i, "invalid element.");
	return (NULL);
}

/**
 * I should pass app, so, depending on which object am i creating, it goes on Object list
 * Light list, camera or ambient light.
 * I can also use this to verify if camera or ambient light is being redifined at any
 * point.
 */
int	parse_line(t_list *line, int i, t_rtapp *app)
{
	t_object	*new_obj;
	char		*aux;
	char		**split;

	aux = (char *) line->content;
	split = ft_split_base(aux, " \t");
	if (!split || !split[0])
	{
		rtlog(RT_ERRLOG, 0, "Failed to parse line %i: %s", i, strerror(errno));
		return (RT_FAILURE);
	}
	rtlog(RT_LOG, 0, "Parsing %s element on line %i.", split[0], i);
	new_obj = parse_element(split, i, app);
	ft_split_free(split);
	if (!new_obj)
		return (RT_FAILURE);
	if (obj_to_app(new_obj, app))
		return (RT_FAILURE);
	rtlog(RT_LOG, 0, "Element initialized.");
	return (RT_SUCCESS);
}
