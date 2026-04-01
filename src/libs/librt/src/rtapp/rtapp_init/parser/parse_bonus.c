/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:40:38 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 17:36:59 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

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

int	parse_line(t_list *line, int i)
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
	free(line->content);
	rtlog(RT_LOG, 0, "Parsing %s element on line %i.", split[0], i);
	line->content = parse_element(split, i);
	ft_split_free(split);
	if (!line->content)
		return (RT_FAILURE);
	rtlog(RT_LOG, 0, "%s element on line %i initialized.", split[0], i);
	return (RT_SUCCESS);
}
