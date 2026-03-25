/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:15:16 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/25 20:20:40 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"

static int	validate_arg(char **split, int i)
{
	const char	*msg;
	const char	*err = "Parser for %s failed in line %i: %s";

	msg = NULL;
	if (!split[1])
		msg = "Plane vector coordinates undeclared.";
	else if (!split[2])
		msg = "Plane vector normal undeclared.";
	else if (!split[3])
		msg = "Plane color undeclared.";
	else if (split[4])
		msg = "Plane has excess arguments declaration.";
	if (msg)
	{
		rtlog(RT_ERRLOG, 0, err, split[0], i, msg);
		return (RT_FAILURE);
	}
	return (RT_SUCCESS);
}

t_object	*parse_plane(char **split, int i)
{
	t_flim			limits;

	if (parse_args(split, i))
		return (NULL);
	limits.min = -FLT_MAX;
	limits.max = FLT_MAX;
	if (parse_vector(split[0], split[1], i, limits))
		return (NULL); 
	limits.min = -1;
	limits.max = 1;
	if (parse_vector(split[0], split[2], i, limits))
		return (NULL);
	if (parse_color(split[0], split[3], i))
		return (NULL);
	return (new_obj(split, new_plane));
}
