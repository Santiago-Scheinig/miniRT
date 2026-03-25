/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/25 21:27:38 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"

int	rtapp_init(int argc, char **argv, t_rtapp *app)
{
	const char	*errmsg = "Failed to initialize app: %s";
	t_list		*objlst;

	errno = 0;
	if (argc != 2)
	{
		rtlog(RT_ERRLOG, 0, errmsg, "invalid number of arguments.");
		return (RT_FAILURE);
	}
	objlst = init_file(argv[1]);
	if (!objlst)
		return (RT_FAILURE);
	if (init_objlst(objlst, argv[1], app))
		return (RT_FAILURE);
	//To erase
	app->logfd.orig_outfd = -1;
	app->logfd.orig_errfd = -1;
	if (init_log(app))
		return (RT_SUCCESS);
	//Til here
	return (RT_SUCCESS);
}

/* rtapp_render()

rtapp_run() */

int rtapp_kill(t_rtapp *app)
{
	const char	*errmsg = "Failure at app termination: %s";

	if (app->objects)
		ft_lstclear(&(app->objects), rtfree);
	if (app->lights)
		ft_lstclear(&(app->lights), rtfree);
	if (app->ambient)
		rtfree(app->ambient);
	if (app->camera)
		rtfree(app->camera);
	//To erase
	if (app->logfd.orig_outfd != -1)
		if (dup2(app->logfd.orig_outfd, STDOUT_FILENO) == -1)
			rtlog(RT_ERRLOG, 0, errmsg, "unable to restore STDOUT_FILENO.");
	if (app->logfd.orig_errfd != -1)
		if (dup2(app->logfd.orig_errfd, STDERR_FILENO) == -1)
			rtlog(RT_ERRLOG, 0, errmsg, "unable to restore STDERR_FILENO.");
	//Til here
	return (RT_SUCCESS);
}