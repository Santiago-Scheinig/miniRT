/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:23:52 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 21:46:41 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"
#include "rtapp_parser.h"

int init_plane(char **argv, int i, t_rtapp *app)
{
	const char		*err = "[line: %i][%s] initialization failed: %s";
	t_elem_plane	*verif;
	t_object		*aux;
	t_list			*new_node;
	
	if (parse_plane(argv, i))
		return (RT_FAILURE);
	aux = new_plane(argv);
	if (!aux)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
	verif = (t_elem_plane *) aux->data;
	if (!verif->normal.x && !verif->normal.y && !verif->normal.z)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], "invalid normal."));
	new_node = ft_lstnew(aux);
	if (!new_node)
	{
		rtfree(aux);
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
	}
	ft_lstadd_back(&(app->objects), new_node);

/* 	verif = ((t_elem_plane *) aux->data);
	rtlog(RT_LOG, 0, "[line: %i] position:\t%f,%f,%f", i, verif->pos.x, verif->pos.y, verif->pos.z);
	rtlog(RT_LOG, 0, "[line: %i] normal:\t\t%f,%f,%f", i, verif->normal.x, verif->normal.y, verif->normal.z);
	rtlog(RT_LOG, 0, "[line: %i] colour:\t\t%i", i, verif->rgb); */

	return (RT_SUCCESS);
}

int init_cylinder(char **argv, int i, t_rtapp *app)
{
	const char		*err = "[line: %i][%s] initialization failed: %s";
	t_elem_cylinder	*verif;
	t_object		*aux;
	t_list			*new_node;
	
	if (parse_cylinder(argv, i))
		return (RT_FAILURE);
	aux = new_cylinder(argv);
	if (!aux)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
	verif = (t_elem_cylinder *) aux->data;
	if (!verif->normal.x && !verif->normal.y && !verif->normal.z)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], "invalid normal."));
	new_node = ft_lstnew(aux);
	if (!new_node)
	{
		rtfree(aux);
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
	}
	ft_lstadd_back(&(app->objects), new_node);

/* 	verif = ((t_elem_cylinder *) aux->data);
	rtlog(RT_LOG, 0, "[line: %i] position:\t%f,%f,%f", i, verif->pos.x, verif->pos.y, verif->pos.z);
	rtlog(RT_LOG, 0, "[line: %i] normal:\t\t%f,%f,%f", i, verif->normal.x, verif->normal.y, verif->normal.z);
	rtlog(RT_LOG, 0, "[line: %i] diameter:\t%f", i, verif->diam);
	rtlog(RT_LOG, 0, "[line: %i] height:\t\t%f", i, verif->height);
	rtlog(RT_LOG, 0, "[line: %i] colour:\t\t%i", i, verif->rgb); */

	return (RT_SUCCESS);
}

int init_sphere(char **argv, int i, t_rtapp *app)
{
	const char		*err = "[line: %i][%s] initialization failed: %s";
	t_object		*aux;
	t_list			*new_node;
	
	if (parse_sphere(argv, i))
		return (RT_FAILURE);
	aux = new_sphere(argv);
	if (!aux)
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
	new_node = ft_lstnew(aux);
	if (!new_node)
	{
		rtfree(aux);
		return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
	}
	ft_lstadd_back(&(app->objects), new_node);

/* 	t_elem_sphere	*verif = ((t_elem_sphere *) aux->data);
	rtlog(RT_LOG, 0, "[line: %i] position:\t%f,%f,%f", i, verif->pos.x, verif->pos.y, verif->pos.z);
	rtlog(RT_LOG, 0, "[line: %i] diameter:\t%f", i, verif->diam);
	rtlog(RT_LOG, 0, "[line: %i] colour:\t\t%i", i, verif->rgb); */

	return (RT_SUCCESS);
}
