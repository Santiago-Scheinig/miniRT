/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:51:07 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 19:41:32 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This is a bonus file, should be changed later on
 */

#include "rtapp_init.h"

static int	dup2_logs(int log_fd, int errlog_fd, t_rtapp *app)
{
	char	*err = "creation of %s file failed: %s";

	if (log_fd != -1)
	{
		if (dup2(log_fd, STDOUT_FILENO) == -1)
		{
			rtlog(RT_ERRLOG, 0, err, "log.txt", strerror(errno));
			app->logfd.orig_outfd = -1;
			return (RT_FAILURE);
		}
		close(log_fd);
	}
	if (errlog_fd != -1)
	{
		if (dup2(errlog_fd, STDERR_FILENO) == -1)
		{
			rtlog(RT_ERRLOG, 0, err, "errlog.txt", strerror(errno));
			app->logfd.orig_errfd = -1;
			return (RT_FAILURE);
		}
		close(errlog_fd);
	}
	return (RT_SUCCESS);
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
	if (dup2_logs(log_fd, errlog_fd, app))
		return (rtlog(RT_LOG, 0, "< Log files initialization failed >"));
	return (rtlog(RT_LOG, 0, "< Log files initialization successfull >"));
}
