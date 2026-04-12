/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:40:22 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 18:11:43 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"
#include "rtapp_parser.h"

static int parse_element(char **arr, int i, t_rtapp *app)
{
    const char  *err = "[line: %i][%s] parser failed: %s";
    int         j;

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
	if (aux[0] == '\n')
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
