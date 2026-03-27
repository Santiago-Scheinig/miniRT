/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:40:22 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/27 17:05:28 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"
#include "rtapp_parser.h"

static void	*get_initializer(char *specifier)
{
	if (!ft_strncmp(specifier, "pl", 3))
		return (&init_plane);
	if (!ft_strncmp(specifier, "cy", 3))
		return (&init_cylinder);
	if (!ft_strncmp(specifier, "sp", 3))
		return (&init_sphere);
	if (!ft_strncmp(specifier, "C", 2))
		return (&init_camera);
	if (!ft_strncmp(specifier, "L", 2))
		return (&init_light);
	if (!ft_strncmp(specifier, "A", 2))
		return (&init_ambient_light);
	return (NULL);
}

static int	parse_element(char **split, int i, t_rtapp *app)
{
	int	(*initializer)(char **, int, t_rtapp *);
	
	initializer = get_initializer(split[0]);
	if (!initializer)
	{
		rtlog(RT_ERRLOG, 0, "Failed to parse line %i: %s", i, "invalid element.");
		return (RT_FAILURE);
	}
	if (initializer(split, i, app))
		return (RT_FAILURE);
	return (RT_FAILURE);
}

int	parse_line(t_list *line, int i, t_rtapp *app)
{
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
	if (parse_element(split, i, app))
	{
		ft_split_free(split);
		return (RT_FAILURE);
	}
	ft_split_free(split);
	rtlog(RT_LOG, 0, "Element initialized.");
	return (RT_SUCCESS);
}
