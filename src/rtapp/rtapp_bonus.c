/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:43:23 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/29 00:00:00 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"
#include "rtapp_render_bonus.h"

int	rtapp_init(int argc, char **argv, t_rtapp *app)
{
	const char	*err = "initialization of miniRT app failed: %s";
	t_list		*lines;

	errno = 0;
	app->bonus.logfd.orig_outfd = -1;
	app->bonus.logfd.orig_errfd = -1;
	if (argc != 2)
		return (rtlog(RT_ERRLOG, 0, err, "invalid number of arguments."));
	lines = init_file(argv[1]);
	if (!lines)
		return (RT_FAILURE);
	if (init_file_contents(lines, argv[1], app))
		return (RT_FAILURE);
	if (init_log(app))
		return (RT_SUCCESS);
	return (RT_SUCCESS);
}

int	rtapp_kill(t_rtapp *app, t_rterr errcode)
{
	const char	*err = "termination of miniRT app failed: %s";

	(void)errcode;
	if (app->objects)
		ft_lstclear(&(app->objects), object_del);
	if (app->lights)
		ft_lstclear(&(app->lights), free);
	if (app->img)
		free(app->img);
	del_mlx(&app->mlx, 0);
	if (app->bonus.logfd.orig_outfd != -1)
		if (dup2(app->bonus.logfd.orig_outfd, STDOUT_FILENO) == -1)
			rtlog(RT_ERRLOG, 0, err, "unable to restore stdout.");
	if (app->bonus.logfd.orig_errfd != -1)
		if (dup2(app->bonus.logfd.orig_errfd, STDERR_FILENO) == -1)
			rtlog(RT_ERRLOG, 0, err, "unable to restore stderr.");
	exit(RT_SUCCESS);
}
