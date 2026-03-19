/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:51:52 by sscheini          #+#    #+#             */
/*   Updated: 2025/07/10 18:19:49 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	long	ft_isspace(long c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

static	long	ft_issign(long c)
{
	if (c == '-')
		return (-1);
	if (c == '+')
		return (1);
	return (0);
}

/**
 * Finds the first number on a STRING with a decimal base.
 * @param str The string where the base number is saved.
 * @return The decimal LONG found on STR.
 * @note A number can, but is not forced to, start with any
 * amount of spaces and one sign; but the next character must 
 * be a digit, if not or str doesn't exists, returns 0.
 */
long	ft_atol(const char *nptr)
{
	long	i;
	long	nbr;
	long	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (ft_isspace(nptr[i]) == 1)
		i++;
	if (ft_issign(nptr[i]))
		sign = ft_issign(nptr[i++]);
	else if (!ft_isdigit(nptr[i]))
		return (nbr);
	if (ft_isdigit(nptr[i]))
		nbr = nptr[i] - 48;
	else
		return (nbr);
	while (ft_isdigit(nptr[i++ + 1]))
		nbr = (nbr * 10) + (nptr[i] - 48);
	return (nbr * sign);
}
