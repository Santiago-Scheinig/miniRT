/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:14:52 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/27 16:43:53 by sscheini         ###   ########.fr       */
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
	t_flim			limits;

	if (validate_arg(split, i))
		return (RT_FAILURE);
	limits.min = -FLT_MAX;
	limits.max = FLT_MAX;
	if (parse_vector(split[0], split[1], i, limits))
		return (RT_FAILURE); 
	limits.min = 0;
	limits.max = FLT_MAX;
	if (parse_float(split[0], split[2], i, limits))
		return (RT_FAILURE);
	if (parse_color(split[0], split[3], i))
		return (RT_FAILURE);
	return (RT_SUCCESS);
}
