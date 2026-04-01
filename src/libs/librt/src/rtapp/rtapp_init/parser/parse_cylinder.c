/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:47:07 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 19:05:21 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

static int	validate_arg(char **split, int i)
{
	const char	*msg;
	const char	*err = "Parser for %s failed in line %i: %s";

	msg = NULL;
	if (!split[1])
		msg = "Cylinder vector coordinates undeclared.";
	else if (!split[2])
		msg = "Cylinder vector normal undeclared.";
	else if (!split[3])
		msg = "Cylinder diameter undeclared.";
	else if (!split[4])
		msg = "Cylinder height undeclared.";
	else if (!split[5])
		msg = "Cylinder color undeclared.";
	else if (split[6])
		msg = "Cylinder has excess arguments declaration.";
	if (msg)
		return (rtlog(RT_ERRLOG, 0, err, split[0], i, msg));
	return (RT_SUCCESS);
}

int	parse_cylinder(char **split, int i)
{
	const char	*msg = "Parser error for %s in line %i: %s";
	t_flim			limits;

	if (validate_arg(split, i))
		return (RT_FAILURE);
	limits.min = -FLT_MAX;
	limits.max = FLT_MAX;
	if (parse_vector(split[0], split[1], i, limits))
		return (rtlog(RT_ERRLOG, 0, msg, split[0], i, "invalid coordinates."));
	limits.min = -1;
	limits.max = 1;
	if (parse_vector(split[0], split[2], i, limits))
		return (rtlog(RT_ERRLOG, 0, msg, split[0], i, "invalid normal.")); 
	limits.min = 0;
	limits.max = FLT_MAX;
	if (parse_float(split[0], split[3], i, limits))
		return (rtlog(RT_ERRLOG, 0, msg, split[0], i, "invalid diameter."));
	if (parse_float(split[0], split[4], i, limits))
		return (rtlog(RT_ERRLOG, 0, msg, split[0], i, "invalid height."));
	if (parse_color(split[0], split[5], i))
		return (rtlog(RT_ERRLOG, 0, msg, split[0], i, "invalid color."));
	return (RT_SUCCESS);
}
