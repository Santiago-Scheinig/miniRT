/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:42:32 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 20:35:22 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

static	int	ft_issign(int c)
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
 * @param base The base in which the number must be found.
 * @return The decimal INT found on STR.
 * @note A number can, but is not forced to, start with any
 * amount of spaces and one sign; but the next character must 
 * be a digit, if not or str doesn't exists, returns 0.
 */
int	ft_atoi(const char *nptr)
{
	int	i;
	int	nbr;
	int	sign;

	if (!nptr)
		return (0);
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
