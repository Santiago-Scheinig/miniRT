/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:13:19 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 18:45:55 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

static int	validate_arg(char **split, int i)
{
	const char	*msg;
	const char	*err = "Parser for %s failed in line %i: %s";

	msg = NULL;
	if (!split[1])
		msg = "Light vector coordinates undeclared.";
	else if (!split[2])
		msg = "Light brightness undeclared.";
	else if (split[3])
		msg = "Light has excess arguments declaration.";
	if (msg)
		return (rtlog(RT_ERRLOG, 0, err, split[0], i, msg));
	return (RT_SUCCESS);
}

int	parse_light(char **split, int i)
{
	const char	*msg = "Parser error for %s in line %i: %s";
	t_flim		limits;

	if (validate_arg(split, i))
		return (RT_FAILURE);
	limits.min = -FLT_MAX;
	limits.max = FLT_MAX;
	if (parse_vector(split[0], split[1], i, limits))
		return (rtlog(RT_ERRLOG, 0, msg, split[0], i, "invalid coordinates."));
	limits.min = -1;
	limits.max = 1;
	if (parse_float(split[0], split[2], i, limits))
		return (rtlog(RT_ERRLOG, 0, msg, split[0], i, "invalid brightness."));
	return (RT_SUCCESS);
}
