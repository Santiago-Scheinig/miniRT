/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:11:26 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/24 20:53:32 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "rtapp.h"

static void *get_constructor(t_elements specifier)
{
	if (specifier == SP)
		return (&new_sphere);
	return (NULL);
}

static t_elements	get_element_id(char *str)
{
	if (!ft_strncmp("SP", str, 2))
		return (SP);
	if (!ft_strncmp("CY", str, 2))
		return (CY);
	if (!ft_strncmp("PL", str, 2))
		return (PL);
	return (INV);
}

static void	*kill_obj(t_object *elm, char **split, int err, int line)
{
	const char	*errmsg[] = {
							"Error allocating '%s' element on line %i.",
							"Invalid '%s' element on line %i.",
							"Unable to find '%s' element on line %i."
						 };
	rtlog(RT_ERRLOG, 0, errmsg[err], split[0], line);
	ft_split_free(split);
	free(elm);
	return (NULL);
}

static void	*new_obj(char *elm_str, int line)
{
	t_object	*elm;
	char		**split;
	void		*(*f)(char **);

	split = ft_split_base(elm_str, " \t");
	if (!split)
		return (NULL);
	free(elm_str);
	elm = ft_calloc(1, sizeof(t_object));
	if (elm)
		return (kill_obj(elm, split, 0, line));
	elm->id = get_element_id(split[0]);
	if (elm->id == INV)
		return (kill_obj(elm, split, 1, line));
	f = (void *(*)(char **)) get_constructor(elm->id);
	if (!f)
		return (kill_obj(elm, split, 2, line));
	elm->obj = f(split);
	if (!elm->obj)
		return (kill_obj(elm, split, 0, line));
	ft_split_free(split);
	return (elm);
}

int	init_objlst(t_list *lines, t_rtapp *app)
{
	t_list		*head;
	int			i;

	rtlog(RT_LOG, 0, "Initializing object list...");
	i = 0;
	head = lines;
	while (lines)
	{
		lines->content = new_obj((char *) lines->content, i);
		if (!lines->content)
		{
			rtapp_kill(app);
			return (RT_FAILURE);
		}
		lines = lines->next;
		i++;
	}
	return (RT_SUCCESS);
}
