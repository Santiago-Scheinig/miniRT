/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_parse_err_msgs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:58:45 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/25 17:32:58 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_PARSE_ERR_MSGS_H
# define G_PARSE_ERR_MSGS_H

# if BONUS
#  include "g_parse_err_msgs_bonus.h"
# else

/**
 * Error messages for point light argument validation.
 * @note Last entry is the excess arguments error. All preceding entries
 * correspond to each expected argument in declaration order.
 */
static const char *const	g_lp_msgs[] = {
	"light coordinates undeclared.",
	"light brightness undeclared.",
	"light color undeclared.",
	"light has excess arguments."
};
# endif

/**
 * Error messages for ambient light argument validation.
 * @note Last entry is the excess arguments error. All preceding entries
 * correspond to each expected argument in declaration order.
 */
static const char *const	g_la_msgs[] = {
	"ambient light ratio undeclared.",
	"ambient light color undeclared.",
	"ambient light has excess arguments."
};

/**
 * Error messages for camera argument validation.
 * @note Last entry is the excess arguments error. All preceding entries
 * correspond to each expected argument in declaration order.
 */
static const char *const	g_ca_msgs[] = {
	"camera vector coordinates undeclared.",
	"camera vector normal undeclared.",
	"camera FOV undeclared.",
	"camera has excess arguments."
};

/**
 * Error messages for plane argument validation.
 * @note Last entry is the excess arguments error. All preceding entries
 * correspond to each expected argument in declaration order.
 */
static const char *const	g_pl_msgs[] = {
	"plane vector coordinates undeclared.",
	"plane vector normal undeclared.",
	"plane color undeclared.",
	"plane has excess arguments."
};

/**
 * Error messages for cylinder argument validation.
 * @note Last entry is the excess arguments error. All preceding entries
 * correspond to each expected argument in declaration order.
 */
static const char *const	g_cy_msgs[] = {
	"cylinder coordinates undeclared.",
	"cylinder normal undeclared.",
	"cylinder diameter undeclared.",
	"cylinder height undeclared.",
	"cylinder color undeclared.",
	"cylinder has excess arguments."
};

/**
 * Error messages for sphere argument validation.
 * @note Last entry is the excess arguments error. All preceding entries
 * correspond to each expected argument in declaration order.
 */
static const char *const	g_sp_msgs[] = {
	"sphere coordinates undeclared.",
	"sphere diameter undeclared.",
	"sphere color undeclared.",
	"sphere has excess arguments."
};

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif