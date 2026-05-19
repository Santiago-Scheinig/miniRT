/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:13:33 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/19 20:25:07 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

int	parse_extention(char *sp, char *str, int i, char *extention)
{
	const char	*err = "[line: %i][%s] parser failed: %s";

	if (!str)
		return (RT_FAILURE);
	if (ft_strnstr(str, extention, ft_strlen(extention) + 1))
		return (rtlog(RT_ERRLOG, 0, err, i, sp, "invalid extention."));
	return (RT_SUCCESS);
}
