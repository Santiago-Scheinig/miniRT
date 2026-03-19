/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:58:50 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:08:21 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static	int	ft_isspecifier(char c)
{
	if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X')
		return (1);
	else if (c == 'c' || c == 's' || c == 'p' || c == '%')
		return (1);
	return (0);
}

/**
 * Sets the presicion value if any is detailed.
 * Returns a pointer to the last character found after reading the digits.
 */
static	const char	*ft_precisioncheck(int *precision, const char *s)
{
	if (*s == '.')
	{
		s++;
		if (ft_isdigit(*s))
			*precision = ft_atoi(s);
		else
			*precision = 0;
	}
	while (ft_isdigit(*s))
		s++;
	return (s);
}

/**
 * Sets the width value if any is detailed.
 * Returns a pointer to the last character found after reading the digits.
 */
static	const char	*ft_widthcheck(int *width, const char *s)
{
	if (ft_isdigit(*s))
		*width = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	return (s);
}

/**
 * Sets the flags | [0 - 1 - 2 - 3 - 4] | to true if called.
 * Returns a pointer to the last character found after reading the flags.
 */
static	const char	*ft_flagcheck(int *flags, const char *s)
{
	while (*s == '-' || *s == '+' || *s == ' ' || *s == '#' || *s == '0')
	{
		if (*s == '-')
			flags[0] = 1;
		if (*s == '+')
			flags[1] = 1;
		if (*s == ' ')
			flags[2] = 1;
		if (*s == '#')
			flags[3] = 1;
		if (*s == '0')
			flags[4] = 1;
		s++;
	}
	return (s);
}

/**
 * Creates an INT * that saves the flags information.
 * - Each position of flags represents a different flag or value assigned.
 * - The following flags are represented with true or false:
 *   | [0] -> '-' | [1] -> '+' | [2] -> 'blank' | [3] -> '#' | [4] -> '0' |
 * - Width is set to 0 in position [5], unless a witdh value is detailed.
 * - Presicion is set to -1 in position [6], unless '.' is called.
 * - The specifier character is detailed in position [7] as ascci value.
 *   | [5] -> Width | [6] -> Presicion | [7] -> Specifier |
 * - If the flag format isn't valid, returns NULL.
 */
int	*ft_flagdescriptor(const char *s)
{
	int		*flags;

	flags = ft_calloc(8, sizeof(int));
	if (!flags)
		return (NULL);
	flags[6]--;
	s = ft_flagcheck(flags, s);
	s = ft_widthcheck(&flags[5], s);
	s = ft_precisioncheck(&flags[6], s);
	if (ft_isspecifier(*s))
		flags[7] = (int) *s;
	else
		return (NULL);
	if (flags[7] == '%')
	{
		ft_bzero(flags, 8);
		flags[6]--;
	}
	if (flags[7] == 'u')
	{
		flags[1] = 0;
		flags[2] = 0;
	}
	return (flags);
}
