/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:43:23 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 18:45:08 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"
#include "rtapp_init.h"

int	rtapp_init(int argc, char **argv, t_rtapp *app)
{
	const char	*err = "initialization of miniRT app failed: %s";
	t_list		*objlst;

	errno = 0;
	if (argc != 2)
		return (rtlog(RT_ERRLOG, 0, err, "invalid number of arguments."));
	objlst = init_file(argv[1]);
	if (!objlst)
		return (RT_FAILURE);
	app->objects = objlst;
	if (init_objlst(app->objects, argv[i]))
		return (RT_FAILURE);
	app->logfd.orig_outfd = -1;
	app->logfd.orig_errfd = -1;
	if (init_log(app))
		return (RT_SUCCESS);
	return (RT_SUCCESS);
}

/* rtapp_render()

rtapp_run() */

int rtapp_kill(t_rtapp *app)
{
	const char	*err = "termination of miniRT app failed: %s";

	if (app->objects)
		ft_lstclear(&(app->objects), rtfree);
	if (app->logfd.orig_outfd != -1)
		if (dup2(app->logfd.orig_outfd, STDOUT_FILENO) == -1)
			rtlog(RT_ERRLOG, 0, err, "unable to restore stdout_fileno.");
	if (app->logfd.orig_errfd != -1)
		if (dup2(app->logfd.orig_errfd, STDERR_FILENO) == -1)
			rtlog(RT_ERRLOG, 0, err, "unable to restore stdout_fileno.");
	return (RT_SUCCESS);
}
