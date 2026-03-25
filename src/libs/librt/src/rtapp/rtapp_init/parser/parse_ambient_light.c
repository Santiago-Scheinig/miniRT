/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:13:15 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/25 21:32:39 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"

static int	validate_arg(char **split, int i)
{
	const char	*msg;
	const char	*err = "Parser for %s failed in line %i: %s";

	msg = NULL;
	if (!split[1])
		msg = "Ambient light ratio undeclared.";
	else if (!split[2])
		msg = "Ambient light color undeclared.";
	else if (split[3])
		msg = "Ambient light has excess arguments declaration.";
	if (msg)
	{
		rtlog(RT_ERRLOG, 0, err, split[0], i, msg);
		return (RT_FAILURE);
	}
	return (RT_SUCCESS);
}

t_elem_light_a parse_ambient_light(char **split, int i)
{
	t_flim			limits;

	if (parse_args(split, i))
		return (NULL);
	limits.min = 0;
	limits.max = 1;
	if (parse_float(split[0], split[1], i, limits))
		return (NULL);
	if (parse_color(split[0], split[3], i))
		return (NULL);
	return (new_ambient_light(split));
}
