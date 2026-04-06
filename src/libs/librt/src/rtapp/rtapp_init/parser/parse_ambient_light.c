/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:13:15 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 17:02:18 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

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
		return (rtlog(RT_ERRLOG, 0, err, split[0], i, msg));
	return (RT_SUCCESS);
}

int	parse_ambient_light(char **split, int i)
{
	const char		*msg = "Parser error for %s in line %i: %s";
	t_flim			limits;

	if (validate_arg(split, i))
		return (RT_FAILURE);
	limits.min = 0;
	limits.max = 1;
	if (parse_double(split[0], split[1], i, limits))
		return (rtlog(RT_ERRLOG, 0, msg, split[0], i, "invalid ratio."));
	if (parse_color(split[0], split[2], i))
		return (rtlog(RT_ERRLOG, 0, msg, split[0], i, "invalid color."));
	return (RT_SUCCESS);
}
