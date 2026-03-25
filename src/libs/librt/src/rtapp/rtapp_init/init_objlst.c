/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:11:26 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/25 21:25:41 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"

int	init_objlst(t_list *lines, char *file, t_rtapp *app)
{
	t_list		*head;
	t_list		*prev;
	t_object	*aux;
	int			i;

	rtlog(RT_LOG, 0, "< Validating '%s' file >");
	i = 0;
	head = lines;
	prev = NULL;
	while (lines)
	{
		if (parse_line(lines, i, app))
		{
			ft_lstclear(&head, free);
			if (prev)
				prev->next = NULL;
			return (RT_FAILURE);
		}
		prev = lines;
		lines = lines->next;
		i++;
	}
	rtlog(RT_LOG, 0, "< '%s' file validated >", file);
	return (RT_SUCCESS);
}
