/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:13:17 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/25 21:31:47 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"

static int	validate_arg(char **split, int i)
{
	const char	*msg;
	const char	*err = "Parser for %s failed in line %i: %s";

	msg = NULL;
	if (!split[1])
		msg = "Camera vector coordinates undeclared.";
	else if (!split[2])
		msg = "Camera vector normal undeclared.";
	else if (!split[3])
		msg = "Camera FOV undeclared.";
	else if (split[4])
		msg = "Camera has excess arguments declaration.";
	if (msg)
	{
		rtlog(RT_ERRLOG, 0, err, split[0], i, msg);
		return (RT_FAILURE);
	}
	return (RT_SUCCESS);
}

t_elem_camera parse_camera(char **split, int i)
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
	limits.max = 180;
	if (parse_float(split[0], split[3], i, limits))
		return (NULL);
	return (new_camera(split));
}
