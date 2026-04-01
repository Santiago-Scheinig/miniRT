/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:13:19 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 17:37:01 by sscheini         ###   ########.fr       */
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
	else if (!split[3])
		msg = "Light color undeclared.";
	else if (split[4])
		msg = "Light has excess arguments declaration.";
	if (msg)
	{
		rtlog(RT_ERRLOG, 0, err, split[0], i, msg);
		return (RT_FAILURE);
	}
	return (RT_SUCCESS);
}

int	parse_light(char **split, int i)
{
	t_flim			limits;

	if (validate_arg(split, i))
		return (RT_FAILURE);
	limits.min = -FLT_MAX;
	limits.max = FLT_MAX;
	if (parse_vector(split[0], split[1], i, limits))
		return (RT_FAILURE); 
	limits.min = -1;
	limits.max = 1;
	if (parse_vector(split[0], split[2], i, limits))
		return (RT_FAILURE);
	limits.min = 0;
	limits.max = 180;
	if (parse_float(split[0], split[3], i, limits))
		return (RT_FAILURE);
	return (RT_SUCCESS);
}
