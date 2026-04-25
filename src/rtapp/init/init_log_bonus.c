/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_log_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:51:07 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/25 17:06:15 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"

/**
 * Redirects stdout and stderr to the given log file descriptors.
 * @param log_fd The file descriptor to redirect stdout to, or -1 to skip.
 * @param errlog_fd The file descriptor to redirect stderr to, or -1 to skip.
 * @param app The T_RTAPP instance whose logfd sentinels are reset on failure.
 * @return RT_SUCCESS if all redirections succeeded, RT_FAILURE if any
 * dup2 call fails, resetting the corresponding logfd field to -1.
 * @note The log file descriptors are closed after dup2 regardless of
 * whether the redirection succeeded.
 */
static int	dup2_logs(int log_fd, int errlog_fd, t_rtapp *app)
{
	const char	*err = "creation of %s file failed: %s";

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

/**
 * Initializes log and error log files and redirects stdout and stderr.
 * @param app The T_RTAPP instance to store the original file descriptors.
 * @return RT_SUCCESS if log files were created and redirected successfully,
 * RT_FAILURE if dup2 redirection fails.
 * @note Saves the original stdout and stderr file descriptors into
 * app->logfd before redirecting so rtapp_kill can restore them on exit.
 * Creates log.txt and errlog.txt with O_TRUNC, clearing previous content.
 * @note BONUS: LOG_APP and LOG_TRC mode flags are stubbed out pending
 * implementation of append vs truncate log behavior selection.
 */
int	init_log(t_rtapp *app)
{
	int	log_fd;
	int	errlog_fd;

	if (!DEV)
		return (RT_SUCCESS);
	app->logfd.orig_outfd = STDOUT_FILENO;
	app->logfd.orig_errfd = STDERR_FILENO;
	rtlog(RT_LOG, 0, "< Initializing log files >");
	log_fd = open("log.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	errlog_fd = open("errlog.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (dup2_logs(log_fd, errlog_fd, app))
		return (rtlog(RT_LOG, 0, "< Log files initialization failed >"));
	return (rtlog(RT_LOG, 0, "< Log files initialization successfull >"));
}
