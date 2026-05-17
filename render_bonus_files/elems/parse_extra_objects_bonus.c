/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extra_objects_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 17:31:17 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/17 17:48:12 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

//Need to change depending on the hyperboloid parsing information
int	parse_hb(char **arr, int i)
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
	//extra steps for texture map and refraction [both optionals] Individual errors for each
	return (RT_SUCCESS);
}

//Need to change depending on the cone parsing information
int	parse_cn(char **arr, int i)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	t_dlim		limits;

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
	//extra steps for texture map and refraction [both optionals] Individual errors for each
	return (RT_SUCCESS);
}

//Need to change depending on the parabole parsing information
int	parse_pb(char **arr, int i)
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
	//extra steps for texture map and refraction [both optionals] Individual errors for each
	return (RT_SUCCESS);
}