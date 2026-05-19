/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 17:31:17 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/19 20:40:59 by sscheini         ###   ########.fr       */
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
	if (arr[e + 1] && arr[e + 2] && arr[e + 3]) //Does this work?
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], msgs[e]));
	return (RT_SUCCESS);
}

int	parse_quadric(char **arr, int i, const char *const *g_msgs)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	int			arrlen;

	if (parse_arg(arr, i, g_msgs, 5))
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
	arrlen = ft_arglen(arr);
	if (arrlen > 4 && arr[4]
		&& parse_double(arr[0], arr[4], i, build_limit(0, FLT_MAX)))
		if (parse_extention(arr[0], arr[4], i, ".map"))
			return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid bonus attributes."));
	if (arrlen > 5 && arr[5]
		&& parse_extention(arr[0], arr[5], i, ".map"))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid bonus attributes."));
	return (RT_SUCCESS);
}

int	parse_sp(char **arr, int i, const char *const *g_msgs)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	int			arrlen;

	if (parse_arg(arr, i, g_msgs, 3))
		return (RT_FAILURE);
	if (parse_vector(arr[0], arr[1], i, build_limit(-FLT_MAX, FLT_MAX)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid coordinates."));
	if (parse_double(arr[0], arr[2], i, build_limit(0, FLT_MAX)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid radius."));
	if (parse_vector(arr[0], arr[3], i, build_limit(0, 255)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid color."));
	arrlen = ft_arglen(arr);
	if (arrlen > 4 && arr[4]
		&& parse_double(arr[0], arr[4], i, build_limit(0, FLT_MAX)))
		if (parse_extention(arr[0], arr[4], i, ".map"))
			return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid bonus attributes."));
	if (arrlen > 5 && arr[5]
		&& parse_extention(arr[0], arr[5], i, ".map"))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid bonus attributes."));
	return (RT_SUCCESS);
}

int	parse_pl(char **arr, int i, const char *const *g_msgs)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	int			arrlen;

	if (parse_arg(arr, i, g_msgs, 3))
		return (RT_FAILURE);
	if (parse_vector(arr[0], arr[1], i, build_limit(-FLT_MAX, FLT_MAX)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid coordinates."));
	if (parse_vector(arr[0], arr[2], i, build_limit(-1, 1)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid normal."));
	if (parse_vector(arr[0], arr[3], i, build_limit(0, 255)))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid color."));
	arrlen = ft_arglen(arr);
	if (arrlen > 4 && arr[4]
		&& parse_double(arr[0], arr[4], i, build_limit(0, FLT_MAX)))
		if (parse_extention(arr[0], arr[4], i, ".map"))
			return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid bonus attributes."));
	if (arrlen > 5 && arr[5]
		&& parse_extention(arr[0], arr[5], i, ".map"))
		return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid bonus attributes."));
	return (RT_SUCCESS);
}
