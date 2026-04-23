/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtlog.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:44:02 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/23 20:33:35 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"

/**
 * Prints a formatted timestamp and process ID to a file descriptor.
 * @param pid The process ID to include in the timestamp.
 * @param fd The file descriptor to print to.
 * @note The timestamp format is [HH:MM:SS][PID] derived from the current
 * system time. Used internally by rtlog to prefix all log messages.
 */
static void	print_hms_timestamp(pid_t pid, int fd)
{
	struct timeval	tv;
	long			total_sec;
	long			hours;
	long			minutes;
	long			seconds;

	gettimeofday(&tv, NULL);
	total_sec = tv.tv_sec;
	hours = (total_sec / 3600) % 24;
	minutes = (total_sec / 60) % 60;
	seconds = total_sec % 60;
	ft_printfd(fd, "[%02d:%02d:%02d][%d]", hours, minutes, seconds, pid);
}

int	rtlog(t_logtype type, pid_t pid, const char *fmt, ...)
{
	va_list			args;
	int				fd;

	if (type == RT_ERRLOG)
		fd = STDERR_FILENO;
	else
		fd = STDOUT_FILENO;
	if (!DEV && type != RT_ERRLOG)
		return (fd - 1);
	va_start(args, fmt);
	if (type == RT_ERRLOG)
		ft_printfd(fd, "ERROR\n");
	print_hms_timestamp(pid, fd);
	ft_printfd(fd, "[INFO]");
	ft_printfd(fd, ": ");
	ft_vprintfd(fd, fmt, args);
	ft_printfd(fd, "\n");
	va_end(args);
	return (fd - 1);
}
