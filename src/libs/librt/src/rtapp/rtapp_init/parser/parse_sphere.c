/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:14:52 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 18:59:21 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

static int	validate_arg(char **split, int i)
{
	const char	*status;
	const char	*err = "[line: %i] parser for %s failed: %s";

	status = NULL;
	if (!split[1])
		status = "sphere vector coordinates undeclared.";
	else if (!split[2])
		status = "sphere diameter undeclared.";
	else if (!split[3])
		status = "sphere color undeclared.";
	else if (split[4])
		status = "sphere has excess arguments declaration.";
	if (status)
	{
		rtlog(RT_ERRLOG, 0, err, split[0], i, status);
		return (RT_FAILURE);
	}
	return (RT_SUCCESS);
}

int	parse_sphere(char **split, int i)
{
	const char	*err = "[line: %i] parser for %s failed: %s";
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
	limits.min = 0;
	limits.max = FLT_MAX;
	if (parse_double(split[0], split[2], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid radius."));
	if (parse_color(split[0], split[3], i))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid color."));
	return (RT_SUCCESS);
}
