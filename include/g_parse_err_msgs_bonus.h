/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_parse_err_msgs_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:58:45 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/19 18:35:42 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_PARSE_ERR_MSGS_BONUS_H
# define G_PARSE_ERR_MSGS_BONUS_H

/**
 * Error messages for point light argument validation.
 * @note Last entry is the excess arguments error. All preceding entries
 * correspond to each expected argument in declaration order.
 */
static const char *const	g_lp_msgs[] = {
	"light coordinates undeclared.",
	"light brighness undeclared.",
	"light color undeclared.",
	"light has excess arguments.",
};

static const char *const	g_cn_msgs[] = {
	"cone coordinates undeclared.",
	"cone normal undeclared.",
	"cone diameter undeclared.",
	"cone height undeclared.",
	"cone color undeclared.",
	"cone has excess arguments.",
};

static const char *const	g_hb_msgs[] = {
	"hyperboloid coordinates undeclared."
	"hyperboloid normal undeclared."
	"hyperboloid diameter undeclared."
	"hyperboloid height undeclared."
	"hyperboloid color undeclared.",
	"hyperboloid has excess arguments.",
};

static const char *const	g_pb_msgs[] = {
	"parabole coordinates undeclared.",
	"parabole normal undeclared.",
	"parabole diameter undeclared.",
	"parabole height undeclared.",
	"parabole color undeclared.",
	"parabole has excess arguments.",
};

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif