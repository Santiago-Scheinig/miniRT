/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rterr.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:19:49 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/22 17:39:24 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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