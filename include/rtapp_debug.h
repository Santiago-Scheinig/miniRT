/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_debug.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:22:21 by sscheini          #+#    #+#             */
/*   Updated: 2026/06/09 18:06:20 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_DEBUG_H
# define RTAPP_DEBUG_H

/*--------------------------------------------------------------------------*/
/*-------------------------------ENUMERATIONS-------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Defines the output channel for the rtlog logging function.
 * @note RT_LOG writes to standard output, RT_ERRLOG writes to standard
 * error.
 */
typedef enum e_logtype
{
	RT_LOG = 1,	// Standard output logging.
	RT_ERRLOG,	// Standard error logging.
}	t_logtype;

/**
 * Defines the return status codes used across the application.
 */
typedef enum e_rterr
{
	RT_SUCCESS, // Operation completed successfully.
	RT_FAILURE, // Operation failed.
}	t_rterr;

/*--------------------------------------------------------------------------*/
/*--------------------------------STRUCTURES--------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Holds the saved file descriptors for the logging system.
 * @note Used to preserve and restore the original stdout and stderr
 * file descriptors when the logging system redirects output.
 */
typedef struct s_rtlog
{
	int	orig_outfd; // Saved original standard output file descriptor.
	int	orig_errfd; // Saved original standard error file descriptor.
}	t_rtlog;

/*--------------------------------------------------------------------------*/
/*-----------------------------------LOG------------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Logs a formatted message to stdout or stderr depending on the log type.
 * @param type The log channel, either RT_LOG for stdout or RT_ERRLOG for
 * stderr.
 * @param pid The process ID to include in the log timestamp.
 * @param fmt The format string for the log message.
 * @param ... Variadic arguments matching the format string.
 * @return RT_SUCCESS (0) when writing to stdout, RT_FAILURE (1) when
 * writing to stderr, matching the fd - 1 convention.
 * @note RT_LOG messages are suppressed unless the DEV flag is set at
 * compile time. RT_ERRLOG messages are always printed regardless of DEV.
 * Each log line is prefixed with a timestamp, process ID and INFO tag.
 */
int	rtlog(t_logtype type, pid_t pid, const char *fmt, ...);

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif