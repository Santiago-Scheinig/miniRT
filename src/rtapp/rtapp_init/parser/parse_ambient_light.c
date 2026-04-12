/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:13:15 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 21:40:30 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

static int	validate_arg(char **split, int i)
{
	const char	*status;
	const char	*err = "[line: %i][%s] parser failed: %s";

	status = NULL;
	if (!split[1])
		status = "ambient light ratio undeclared.";
	else if (!split[2])
		status = "ambient light color undeclared.";
	else if (split[3])
		status = "ambient light has excess arguments declaration.";
	if (status)
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], status));
	return (RT_SUCCESS);
}

int	parse_ambient_light(char **split, int i)
{
	const char		*err = "[line: %i][%s] parser failed: %s";
	t_flim			limits;

	if (validate_arg(split, i))
		return (RT_FAILURE);
	limits.min = 0;
	limits.max = 1;
	if (parse_double(split[0], split[1], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid ratio."));
	if (parse_color(split[0], split[2], i))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid color."));
	return (RT_SUCCESS);
}
