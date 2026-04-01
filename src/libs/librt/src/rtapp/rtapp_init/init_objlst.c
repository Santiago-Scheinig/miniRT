/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:11:26 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/27 17:13:29 by sscheini         ###   ########.fr       */
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
	t_list		*head;
	int			i;

	rtlog(RT_LOG, 0, "< Validating '%s' file >", file);
	i = 0;
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
	rtlog(RT_LOG, 0, "< '%s' file validated >", file);
	return (RT_SUCCESS);
}
