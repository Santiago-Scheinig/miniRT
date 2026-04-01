/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:51:07 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/25 20:30:03 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This is a bonus file, should be changed later on
 */

#include "rtapp_init.h"

static void	dup2_logs(int log_fd, int errlog_fd, t_rtapp *app)
{
	char	*msg = "Unable to initialize %s: %s";

	if (log_fd != -1)
	{
		if (dup2(log_fd, STDOUT_FILENO) == -1)
		{
			rtlog(RT_ERRLOG, 0, msg, "log.txt", strerror(errno));
			app->logfd.orig_outfd = -1;
		}
		close(log_fd);
	}
	rtlog(RT_LOG, 0, "STDOUT_FILENO fd redirected to log.txt");
	if (errlog_fd != -1)
	{
		if (dup2(errlog_fd, STDERR_FILENO) == -1)
		{
			rtlog(RT_ERRLOG, 0, msg, "errlog.txt", strerror(errno));
			app->logfd.orig_errfd = -1;
		}
		close(errlog_fd);
	}
	rtlog(RT_LOG, 0, "STDERR_FILENO fd redirected to errlog.txt");
}

int	init_log(t_rtapp *app)
{
	//int	mode;
	int	log_fd;
	int	errlog_fd;

/* 	if (LOG_APP)
		mode = O_APPEND;
	if (LOG_TRC)
		mode = O_TRUNC; 
	if (!DEV)
		return (RT_SUCCESS); */
	app->logfd.orig_outfd = STDOUT_FILENO;
	app->logfd.orig_errfd = STDERR_FILENO;
	rtlog(RT_LOG, 0, "< Initializing log files >");
	log_fd = open("log.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	errlog_fd = open("errlog.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	rtlog(RT_LOG, 0, "< Log files successfully initialized >");
	dup2_logs(log_fd, errlog_fd, app);
	return (RT_SUCCESS);
}
