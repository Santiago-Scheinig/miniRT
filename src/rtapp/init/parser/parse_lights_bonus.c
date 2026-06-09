/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:44:55 by sscheini          #+#    #+#             */
/*   Updated: 2026/06/09 17:41:07 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

static int	parse_arg(char **arr, int i, const char *const *msgs, int e)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	int			j;

	j = -1;
	while (++j < e)
		if (!arr[j + 1])
			return (rtlog(RT_ERRLOG, 0, err, i, arr[0], msgs[j]));
	if (arr[e + 1])
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], msgs[e]));
	return (RT_SUCCESS);
}

int	parse_camera(char **arr, int i)
{
	const char	*err = "[line: %i][%s] parser failed: %s";

	if (parse_arg(arr, i, g_ca_msgs, 3))
		return (RT_FAILURE);
	if (parse_vector(arr[0], arr[1], i, build_limit(-FLT_MAX, FLT_MAX)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid coordinates."));
	if (parse_vector(arr[0], arr[2], i, build_limit(-1, 1)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid normal."));
	if (parse_double(arr[0], arr[3], i, build_limit(0, 180)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid FOV."));
	return (RT_SUCCESS);
}

int	parse_lp(char **split, int i)
{
	const char	*err = "[line: %i][%s] parser failed: %s";

	if (parse_arg(split, i, g_lp_msgs, 3))
		return (RT_FAILURE);
	if (parse_vector(split[0], split[1], i, build_limit(-FLT_MAX, FLT_MAX)))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid coordinates."));
	if (parse_double(split[0], split[2], i, build_limit(0, 1)))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid brightness."));
	if (parse_vector(split[0], split[3], i, build_limit(0, 255)))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid color."));
	return (RT_SUCCESS);
}

int	parse_la(char **split, int i)
{
	const char		*err = "[line: %i][%s] parser failed: %s";

	if (parse_arg(split, i, g_la_msgs, 2))
		return (RT_FAILURE);
	if (parse_double(split[0], split[1], i, build_limit(0, 1)))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid ratio."));
	if (parse_vector(split[0], split[2], i, build_limit(0, 255)))
		return (rtlog(RT_ERRLOG, 0, err, i, split[0], "invalid color."));
	return (RT_SUCCESS);
}
