/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:44:55 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/17 17:33:55 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

int	parse_camera(char **arr, int i)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	t_dlim		limits;

	if (parse_arg(arr, i, g_ca_msgs, 3))
		return (RT_FAILURE);
	limits.min = -FLT_MAX;
	limits.max = FLT_MAX;
	if (parse_vector(arr[0], arr[1], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid coordinates."));
	limits.min = -1;
	limits.max = 1;
	if (parse_vector(arr[0], arr[2], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid normal."));
	limits.min = 0;
	limits.max = 180;
	if (parse_double(arr[0], arr[3], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid FOV."));
	return (RT_SUCCESS);
}

int	parse_lp(char **split, int i)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	t_dlim		limits;

	if (parse_arg(split, i, g_lp_msgs_bonus, 3))
		return (RT_FAILURE);
	limits.min = -FLT_MAX;
	limits.max = FLT_MAX;
	if (parse_vector(split[0], split[1], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid coordinates."));
	limits.min = -1;
	limits.max = 1;
	if (parse_double(split[0], split[2], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid brightness."));
	limits.min = 0;
	limits.max = 255;
	if (parse_vector(split[0], split[3], i))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid color."));
	return (RT_SUCCESS);
}

int	parse_la(char **split, int i)
{
	const char		*err = "[line: %i][%s] parser failed: %s";
	t_dlim			limits;

	if (parse_arg(split, i, g_la_msgs, 2))
		return (RT_FAILURE);
	limits.min = 0;
	limits.max = 1;
	if (parse_double(split[0], split[1], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid ratio."));
	limits.min = 0;
	limits.max = 255;
	if (parse_vector(split[0], split[2], i))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid color."));
	return (RT_SUCCESS);
}
