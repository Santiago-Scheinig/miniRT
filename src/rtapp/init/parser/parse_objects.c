/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:41:26 by sscheini          #+#    #+#             */
/*   Updated: 2026/06/09 17:41:23 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

static int	parse_req_att(char **arr, int i, const char *const *msgs, int e)
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

int	parse_quadric(char **arr, int i, const char *const *g_msgs)
{
	const char	*err = "[line: %i][%s] parser failed: %s";

	if (parse_req_att(arr, i, g_msgs, 5))
		return (RT_FAILURE);
	if (parse_vector(arr[0], arr[1], i, build_limit(-FLT_MAX, FLT_MAX)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid coordinates."));
	if (parse_vector(arr[0], arr[2], i, build_limit(-1, 1)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid normal."));
	if (parse_double(arr[0], arr[3], i, build_limit(0, FLT_MAX)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid diameter."));
	if (parse_double(arr[0], arr[4], i, build_limit(0, FLT_MAX)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid height."));
	if (parse_vector(arr[0], arr[5], i, build_limit(0, 255)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid color."));
	return (RT_SUCCESS);
}

int	parse_sp(char **arr, int i, const char *const *g_msgs)
{
	const char	*err = "[line: %i][%s] parser failed: %s";

	if (parse_req_att(arr, i, g_msgs, 3))
		return (RT_FAILURE);
	if (parse_vector(arr[0], arr[1], i, build_limit(-FLT_MAX, FLT_MAX)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid coordinates."));
	if (parse_double(arr[0], arr[2], i, build_limit(0, FLT_MAX)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid radius."));
	if (parse_vector(arr[0], arr[3], i, build_limit(0, 255)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid color."));
	return (RT_SUCCESS);
}

int	parse_pl(char **arr, int i, const char *const *g_msgs)
{
	const char	*err = "[line: %i][%s] parser failed: %s";

	if (parse_req_att(arr, i, g_msgs, 3))
		return (RT_FAILURE);
	if (parse_vector(arr[0], arr[1], i, build_limit(-FLT_MAX, FLT_MAX)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid coordinates."));
	if (parse_vector(arr[0], arr[2], i, build_limit(-1, 1)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid normal."));
	if (parse_vector(arr[0], arr[3], i, build_limit(0, 255)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid color."));
	return (RT_SUCCESS);
}
