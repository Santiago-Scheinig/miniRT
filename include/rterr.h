/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rterr.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:19:49 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/22 18:27:31 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>

typedef enum e_logtype
{
	RTLOG_LOG = 1,
	RTLOG_ERR,
}	t_logtype;

typedef enum e_rterr
{
	RTERR_SUCCESS,
	RTERR_FAILURE,
	RTERR_INVARGC,
	RTERR_INVCHAR,
	RTERR_INVARGV,
	RTERR_LOGINIT,
	RTERR_MEMINIT,
}	t_rterr;

void	log(t_logtype type, pid_t pid, const char *fmt, ...);