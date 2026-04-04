/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:11:26 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 19:51:08 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"
#include "rtapp_init.h"

t_object	*new_obj(char **split, t_object *(*constructor)(char **))
{
	t_object		*obj;
	const char		*errmsg = "Failed to initialize %s: %s";

	obj = constructor(split);
	if (!obj)
	{
		rtlog(RT_ERRLOG, 0, errmsg, split[0], strerror(errno));
		free(obj);
		return (NULL);
	}
	return (obj);
}

int	init_objlst(t_list *lines, char *file, t_rtapp *app)
{
	const char	*errmsg = "Failed to validate %s: %s";
	t_list		*head;
	int			i;

	rtlog(RT_LOG, 0, "< Validating '%s' file >", file);
	i = 0;
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
		return (rtlog(RT_ERRLOG, 0, errmsg, file, "no ambient light defined."));
	if (app->camera.fov == -1)
		return (rtlog(RT_ERRLOG, 0, errmsg, file, "no camera defined."));
	return (rtlog(RT_LOG, 0, "< '%s' file validated >", file));
}
