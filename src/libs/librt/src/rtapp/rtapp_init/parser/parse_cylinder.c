/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:47:07 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/25 20:20:13 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"

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
	{
		rtlog(RT_ERRLOG, 0, err, split[0], i, msg);
		return (RT_FAILURE);
	}
	return (RT_SUCCESS);
}

t_object	*parse_cylinder(char **split, int i)
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
	limits.min = 0;
	limits.max = FLT_MAX;
	if (parse_float(split[0], split[3], i, limits))
		return (NULL);
	if (parse_float(split[0], split[4], i, limits))
		return (NULL);
	if (parse_color(split[0], split[5], i))
		return (NULL);
	return (new_obj(split, new_cylinder));
}
