/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rterr_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:44:02 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/22 18:34:47 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rterr.h"

static int	get_ms()
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_sec / 1000);
}

void	log(t_logtype type, pid_t pid, const char *fmt, ...)
{
	va_list	args;
	long	ms;
	int		fd;

	if (type == RTLOG_ERR)
		fd = STDERR_FILENO;
	else
		fd = STDOUT_FILENO;
	va_start(args, fmt);
	if (type == RTLOG_ERR)
		ft_printfd(fd, "ERROR\n");
	ft_printfd(fd, "[%010ldms][pid:%d]", get_ms(), pid);
	if (type == RTLOG_LOG)
		ft_printfd(fd, "[INFO]");
	ft_printfd(fd, ": ");
	ft_vprintfd(fd, fmt, args);
	ft_printfd(fd, "\n");
	va_end(args);
}