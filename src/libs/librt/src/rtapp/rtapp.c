/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/24 19:35:41 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"
#include "rtapp_init.h"

int	rtapp_init(int argc, char **argv, t_rtapp *app)
{
	t_list	*aux;

	if (argc != 2)
	{
		rtlog(RT_ERRLOG, 0, "Invalid number of arguments");
		return (RT_FAILURE);
	}
	aux = init_file(argv[1]);
	if (!aux)
		return (RT_FAILURE);
	app->objects = aux;
	app->logfd.orig_outfd = -1;
	app->logfd.orig_errfd = -1;
	if (init_objlst(aux, app))
		return (RT_FAILURE);
	rtlog(RT_LOG, 0, "objects list initialized.");
	if (init_log(app))
		return (RT_SUCCESS);
	return (RT_SUCCESS);
}

/* rtapp_render()

rtapp_run() */

int rtapp_kill(t_rtapp *app)
{
	if (app->objects)
		ft_lstclear(&(app->objects), free);
	if (app->logfd.orig_outfd != -1)
		if (dup2(app->logfd.orig_outfd, STDOUT_FILENO) == -1)
			rtlog(RT_ERRLOG, 0, "Unable to restore STDOUT_FILENO.");
	if (app->logfd.orig_errfd != -1)
		if (dup2(app->logfd.orig_errfd, STDERR_FILENO) == -1)
			rtlog(RT_ERRLOG, 0, "Unable to restore STDERR_FILENO.");
	return (RT_SUCCESS);
}