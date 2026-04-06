/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:14:52 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 17:01:48 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

static int	validate_arg(char **split, int i)
{
	const char	*msg;
	const char	*err = "Parser for %s failed in line %i: %s";

	msg = NULL;
	if (!split[1])
		msg = "Sphere vector coordinates undeclared.";
	else if (!split[2])
		msg = "Sphere diameter undeclared.";
	else if (!split[3])
		msg = "Sphere color undeclared.";
	else if (split[4])
		msg = "Sphere has excess arguments declaration.";
	if (msg)
	{
		rtlog(RT_ERRLOG, 0, err, split[0], i, msg);
		return (RT_FAILURE);
	}
	return (RT_SUCCESS);
}

int	parse_sphere(char **split, int i)
{
	const char	*errmsg = "Parser error for %s in line %i: %s";
	t_flim		limits;

	if (validate_arg(split, i))
		return (RT_FAILURE);
	limits.min = -FLT_MAX;
	limits.max = FLT_MAX;
	if (parse_vector(split[0], split[1], i, limits))
	{
		rtlog(RT_ERRLOG, 0, errmsg, split[0], i, "invalid coordinates.");
		return (RT_FAILURE); 
	}
	limits.min = 0;
	limits.max = FLT_MAX;
	if (parse_double(split[0], split[2], i, limits))
		return (rtlog(RT_ERRLOG, 0, errmsg, split[0], i, "invalid radius."));
	if (parse_color(split[0], split[3], i))
		return (rtlog(RT_ERRLOG, 0, errmsg, split[0], i, "invalid color."));
	return (RT_SUCCESS);
}
