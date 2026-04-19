/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:11:26 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 21:00:23 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"
#include "rtapp_init.h"

int	init_objlst(t_list *lines, char *file, t_rtapp *app)
{
	const char	*err = "compilation of %s file failed: %s";
	t_list		*head;
	int			i;

	rtlog(RT_LOG, 0, "< Compiling '%s' file >", file);
	i = 1;
	app->ambient.ratio = -1;
	app->camera.fov = -1;
	head = lines;
	while (lines)
	{
		if (parse_line(lines, i, app))
		{
			ft_lstclear(&head, free);
			return (RT_FAILURE);
		}
		lines = lines->next;
		i++;
	}
	ft_lstclear(&head, free);
	if (app->ambient.ratio == -1)
		return (rtlog(RT_ERRLOG, 0, err, file, "no ambient light defined."));
	if (app->camera.fov == -1)
		return (rtlog(RT_ERRLOG, 0, err, file, "no camera defined."));
	return (rtlog(RT_LOG, 0, "< Compilation successfull >", file));
}
