/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/22 20:09:21 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"

int	rtapp_init(int argc, char **argv, t_rtapp *app)
{
	t_list	*aux;

	if (argc != 2)
	{
		rtlog(RT_ERRLOG, 0, "Invalid number of arguments");
		return (RT_FAILURE);
	}
	aux = parser(argv[1]);
	if (!aux)
		return (RT_FAILURE);
	app->objects = aux;
	if (init_log(app))
		return (RT_SUCCESS);
/* 	if (init_objlst(aux, app))
		return (RT_FAILURE); *///errlog("[ms][pid]: Unable to initialize the necesary memory to run the application\n";
	//log("[ms][pid]: objects list initializated.");
	//log("[ms][pid]: rtapp_init succesfull.");
	return (RT_SUCCESS);
}

/* rtapp_render()

rtapp_run() */

int rtapp_kill(t_rtapp *app)
{
	if (app->objects)
		ft_lstclear(&(app->objects), free);
	return (RT_SUCCESS);
}