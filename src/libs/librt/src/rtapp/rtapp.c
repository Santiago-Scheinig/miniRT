/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 18:30:54 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"
#include "rtapp_init.h"

int	rtapp_init(int argc, char **argv, t_rtapp *app)
{
	const char	*errmsg = "Failed to initialize app: %s";
	t_list		*lines;

	errno = 0;
	if (argc != 2)
		return (rtlog(RT_ERRLOG, 0, errmsg, "invalid number of arguments."));
	lines = init_file(argv[1]);
	if (!lines)
		return (RT_FAILURE);
	if (init_objlst(lines, argv[1], app))
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

int rtapp_kill(t_rtapp *app, t_rterr errcode)
{
	const char	*errmsg = "Failure at app termination: %s";

	if (app->objects)
		ft_lstclear(&(app->objects), rtfree);
	if (app->lights)
		ft_lstclear(&(app->lights), rtfree);
	//To erase
	if (app->logfd.orig_outfd != -1)
		if (dup2(app->logfd.orig_outfd, STDOUT_FILENO) == -1)
			rtlog(RT_ERRLOG, 0, errmsg, "unable to restore STDOUT_FILENO.");
	if (app->logfd.orig_errfd != -1)
		if (dup2(app->logfd.orig_errfd, STDERR_FILENO) == -1)
			rtlog(RT_ERRLOG, 0, errmsg, "unable to restore STDERR_FILENO.");
	//Til here
	exit(errcode);
}