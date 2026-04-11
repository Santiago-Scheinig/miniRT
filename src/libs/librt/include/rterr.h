/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rterr.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:19:49 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 17:52:18 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTERR_H
# define RTERR_H
# include "libft.h"
# include "rtelm.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/types.h>

typedef enum e_logtype
{
	RT_LOG = 1,
	RT_ERRLOG,
}	t_logtype;

typedef enum e_rterr
{
	RT_SUCCESS,
	RT_FAILURE,
}	t_rterr;

typedef struct s_rtlog
{
	int	orig_outfd;
	int	orig_errfd;
}	t_rtlog;

int		rtlog(t_logtype type, pid_t pid, const char *fmt, ...);

void	rtfree(void *content);

#endif