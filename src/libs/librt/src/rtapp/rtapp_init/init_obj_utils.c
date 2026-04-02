/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:23:52 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 18:31:58 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"
#include "rtapp_parser.h"

int init_plane(char **argv, int i, t_rtapp *app)
{
	const char	*errmsg = "Failed to initialize %s: %s";
	t_object	*aux;
	t_list		*new_node;
	
	if (parse_plane(argv, i))
		return (RT_FAILURE);
	aux = new_obj(argv, &new_plane);
	if (!aux)
		return (RT_FAILURE);
	new_node = ft_lstnew(aux);
	if (!new_node)
	{
		rtfree(aux);
		return (rtlog(RT_ERRLOG, 0, errmsg, argv[0], strerror(errno)));
	}
	ft_lstadd_back(&(app->objects), new_node);
	return (RT_SUCCESS);
}

int init_cylinder(char **argv, int i, t_rtapp *app)
{
	const char	*errmsg = "Failed to initialize %s: %s";
	t_object	*aux;
	t_list		*new_node;
	
	if (parse_cylinder(argv, i))
		return (RT_FAILURE);
	aux = new_obj(argv, &new_cylinder);
	if (!aux)
		return (RT_FAILURE);
	new_node = ft_lstnew(aux);
	if (!new_node)
	{
		rtfree(aux);
		return (rtlog(RT_ERRLOG, 0, errmsg, argv[0], strerror(errno)));
	}
	ft_lstadd_back(&(app->objects), new_node);
	return (RT_SUCCESS);
}

int init_sphere(char **argv, int i, t_rtapp *app)
{
	const char	*errmsg = "Failed to initialize %s: %s";
	t_object	*aux;
	t_list		*new_node;
	
	if (parse_sphere(argv, i))
		return (RT_FAILURE);
	aux = new_obj(argv, &new_sphere);
	if (!aux)
		return (RT_FAILURE);
	new_node = ft_lstnew(aux);
	if (!new_node)
	{
		rtfree(aux);
		return (rtlog(RT_ERRLOG, 0, errmsg, argv[0], strerror(errno)));
	}
	ft_lstadd_back(&(app->objects), new_node);
	return (RT_SUCCESS);
}
