/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:56:40 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 17:09:10 by sscheini         ###   ########.fr       */
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

static	int	ft_isdecimal(int c)
{
	if (c == '.')
		return (1);
	return (0);
}

static	void	ft_getprecision(const char *nptr, double *nbr)
{
	int		i;
	double	frac;
	double	div;

	i = 0;
	frac = 0;
	div = 1;
	while (ft_isdigit(nptr[i]))
	{
		frac = (frac * 10) + (nptr[i++] - '0');
		div *= 10;
	}
	(*nbr) += frac / div;
}

/**
 * Finds the first number on a STRING with a decimal base.
 * @param str The string where the base number is saved.
 * @param base The base in which the number must be found.
 * @return The decimal INT found on STR.
 * @note A number can, but is not forced to, start with any
 * amount of spaces and one sign; but the next character must a
 * be a digit, if not or str doesn't exists, returns 0.
 */
double	ft_atod(const char *nptr)
{
	int		i;
	int		sign;
	double	nbr;

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
	while (ft_isdigit(nptr[i]))
		nbr = (nbr * 10) + (nptr[i++] - '0');
	if (ft_isdecimal(nptr[i]))
		ft_getprecision(&nptr[++i], &nbr);
	return (nbr * sign);
}
