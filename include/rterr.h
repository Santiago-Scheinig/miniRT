/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rterr.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:19:49 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/22 19:56:12 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>

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

void	rtlog(t_logtype type, pid_t pid, const char *fmt, ...);