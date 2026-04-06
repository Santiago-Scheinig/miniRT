/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:13:19 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 18:58:11 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

static int	validate_arg(char **split, int i)
{
	const char	*status;
	const char	*err = "[line: %i] parser for %s failed: %s";

	status = NULL;
	if (!split[1])
		status = "light vector coordinates undeclared.";
	else if (!split[2])
		status = "light brightness undeclared.";
	else if (split[3])
		status = "light has excess arguments declaration.";
	if (status)
		return (rtlog(RT_ERRLOG, 0, err, split[0], i, status));
	return (RT_SUCCESS);
}

int	parse_light(char **split, int i)
{
	const char	*err = "[line: %i] parser for %s failed: %s";
	t_flim		limits;

	if (validate_arg(split, i))
		return (RT_FAILURE);
	limits.min = -FLT_MAX;
	limits.max = FLT_MAX;
	if (parse_vector(split[0], split[1], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid coordinates."));
	limits.min = -1;
	limits.max = 1;
	if (parse_double(split[0], split[2], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid brightness."));
	return (RT_SUCCESS);
}
