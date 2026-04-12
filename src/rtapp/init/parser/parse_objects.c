/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:41:26 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 17:40:31 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

int	parse_camera(char **arr, int i)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	t_dlim			limits;

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

int	parse_pl(char **arr, int i)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	t_dlim		limits;

	if (parse_arg(arr, i, g_pl_msgs, 3))
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
	limits.max = 255;
	if (parse_vector(arr[0], arr[3], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid color."));
	return (RT_SUCCESS);
}

int	parse_cy(char **arr, int i)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	t_dlim			limits;

	if (parse_arg(arr, i, g_cy_msgs, 5))
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
	limits.max = FLT_MAX;
	if (parse_double(arr[0], arr[3], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid diameter."));
	if (parse_double(arr[0], arr[4], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid height."));
	limits.min = 0;
	limits.max = 255;
	if (parse_vector(arr[0], arr[5], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid color."));
	return (RT_SUCCESS);
}

int	parse_sp(char **arr, int i)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	t_dlim		limits;

	if (parse_arg(arr, i, g_sp_msgs, 3))
		return (RT_FAILURE);
	limits.min = -FLT_MAX;
	limits.max = FLT_MAX;
	if (parse_vector(arr[0], arr[1], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid coordinates."));
	limits.min = 0;
	limits.max = FLT_MAX;
	if (parse_double(arr[0], arr[2], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid radius."));
	limits.min = 0;
	limits.max = 255;
	if (parse_vector(arr[0], arr[3], i, limits))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid color."));
	return (RT_SUCCESS);
}
