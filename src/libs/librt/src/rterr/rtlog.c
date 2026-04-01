/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtlog.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:44:02 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 19:51:37 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rterr.h"

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
	
/* 	if (!DEV && type != RT_ERRLOG)
		return; */
	if (type == RT_ERRLOG)
		fd = STDERR_FILENO;
	else
		fd = STDOUT_FILENO;
	va_start(args, fmt);
	if (type == RT_ERRLOG)
		ft_printfd(fd, "ERROR\n");
	print_hms_timestamp(pid, fd);
	if (type == RT_LOG)
		ft_printfd(fd, "[INFO]");
	ft_printfd(fd, ": ");
	ft_vprintfd(fd, fmt, args);
	ft_printfd(fd, "\n");
	va_end(args);
	return (fd - 1);
}
