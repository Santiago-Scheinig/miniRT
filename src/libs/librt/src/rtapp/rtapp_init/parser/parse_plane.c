/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:15:16 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 21:44:45 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

static int	validate_arg(char **split, int i)
{
	const char	*status;
	const char	*err = "[line: %i][%s] parser failed: %s";

	status = NULL;
	if (!split[1])
		status = "plane vector coordinates undeclared.";
	else if (!split[2])
		status = "plane vector normal undeclared.";
	else if (!split[3])
		status = "plane color undeclared.";
	else if (split[4])
		status = "plane has excess arguments declaration.";
	if (status)
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], status));
	return (RT_SUCCESS);
}

int	parse_plane(char **split, int i)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	t_flim		limits;

	if (validate_arg(split, i))
		return (RT_FAILURE);
	limits.min = -FLT_MAX;
	limits.max = FLT_MAX;
	if (parse_vector(split[0], split[1], i, limits))
	{
		rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid coordinates.");
		return (RT_FAILURE); 
	}
	limits.min = -1;
	limits.max = 1;
	if (parse_vector(split[0], split[2], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid normal."));
	if (parse_color(split[0], split[3], i))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid color."));
	return (RT_SUCCESS);
}
