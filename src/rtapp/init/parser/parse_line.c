/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:40:22 by sscheini          #+#    #+#             */
/*   Updated: 2026/06/09 17:41:17 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"
#include "rtapp_parser.h"
#include "g_init_dispatch.h"

static int	is_empty_or_comment_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '#')
			return (TRUE);
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (FALSE);
	}
	return (TRUE);
}

/**
 * Looks up and calls the initializer for a scene element by its specifier.
 * @param arr The array of strings where arr[0] is the element specifier
 * and the remaining entries are its parameters.
 * @param i The line number in the scene file, used for error logging.
 * @param app The T_RTAPP instance to initialize the element into.
 * @return RT_SUCCESS if the element was initialized, RT_FAILURE if the
 * specifier is not found in the dispatch table or initialization fails.
 * @note Dispatches through g_dispatch using exact specifier matching.
 * Replace g_dispatch with the bonus version to support extra elements.
 */
static int	parse_element(char **arr, int i, t_rtapp *app)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	int			j;

	j = 0;
	while (g_dispatch[j].specifier)
	{
		if (!ft_strncmp(arr[0], g_dispatch[j].specifier,
				ft_strlen(g_dispatch[j].specifier) + 1))
		{
			rtlog(RT_LOG, 0, "[line: %i][%s] initializing element.", i, arr[0]);
			return (g_dispatch[j].initializer(arr, i, app));
		}
		j++;
	}
	return (rtlog(RT_ERRLOG, 0, err, i, arr[0], "invalid element."));
}

int	parse_line(t_list *line, int i, t_rtapp *app)
{
	const char	*err = "[line: %i] parser failed: %s";
	char		*aux;
	char		**arr;

	aux = (char *) line->content;
	if (is_empty_or_comment_line(aux))
		return (RT_SUCCESS);
	arr = ft_split_base(aux, " \t\n");
	if (!arr || !arr[0])
		return (rtlog(RT_ERRLOG, 0, err, i, strerror(errno)));
	rtlog(RT_LOG, 0, "[line: %i][%s] parsing element.", i, arr[0]);
	if (parse_element(arr, i, app))
	{
		ft_split_free(arr);
		return (RT_FAILURE);
	}
	rtlog(RT_LOG, 0, "[line: %i][%s] element created.", i, arr[0]);
	ft_split_free(arr);
	return (RT_SUCCESS);
}
