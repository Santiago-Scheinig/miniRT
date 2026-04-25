/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:44:55 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/23 20:22:08 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

int	parse_lp(char **arr, int i)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	t_dlim		limits;

	if (parse_arg(arr, i, g_lp_msgs, 2))
		return (RT_FAILURE);
	limits.min = -FLT_MAX;
	limits.max = FLT_MAX;
	if (parse_vector(arr[0], arr[1], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid coordinates."));
	limits.min = -1;
	limits.max = 1;
	if (parse_double(arr[0], arr[2], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid brightness."));
	return (RT_SUCCESS);
}

int	parse_la(char **arr, int i)
{
	const char		*err = "[line: %i][%s] parser failed: %s";
	t_dlim			limits;

	if (parse_arg(arr, i, g_la_msgs, 2))
		return (RT_FAILURE);
	limits.min = 0;
	limits.max = 1;
	if (parse_double(arr[0], arr[1], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid ratio."));
	limits.min = 0;
	limits.max = 255;
	if (parse_vector(arr[0], arr[2], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid color."));
	return (RT_SUCCESS);
}
