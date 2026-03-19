/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:44:50 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 20:59:46 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Swap and reverses all the characters of a STRING.
 * @param str The string to swap.
 * @return The modified string.
 * @note This functions modifies the original str, doesn't allocate
 * a new one.
 */
static	char	*ft_swap(char *str)
{
	char	swap;
	int		len;
	int		i;

	i = 0;
	if (str[0] == '-')
		i++;
	len = ft_strlen(str);
	while (i < len - 1)
	{
		swap = str[len - 1];
		str[len - 1] = str[i];
		str[i] = swap;
		i++;
		len--;
	}
	return (str);
}

/**
 * Allocates a STRING to save an INT number into.
 * @param n The number to be written.
 * @param len The digit lenght of the number.
 * @return A pointer to the STRING.
 */
static	char	*ft_setstr(int n, int len)
{
	char	*str;

	if (n < 0)
	{
		str = ft_calloc(len + 2, 1);
		if (!str)
			return (NULL);
		str[0] = '-';
	}
	else
	{
		str = ft_calloc(len + 1, 1);
		if (!str)
			return (NULL);
	}
	return (str);
}

/**
 * Creates and allocates a STRING with the INT_MIN number
 * writen on it.
 * @return A pointer to the STRING.
 */
static	char	*ft_min(void)
{
	char	*str;

	str = ft_itoa(INT_MIN + 1);
	if (!str)
		return (NULL);
	str[ft_strlen(str) - 1]++;
	return (str);
}

/**
 * Counts the amount of digits that an INT variable has.
 * @param n The number which to count it's digits.
 * @return The amount of digits counted. 
 */
static	int	ft_nbrlen(int n)
{
	int	count;

	n = n * 1;
	count = 1;
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

/**
 * Creates and allocates a STRING writen with the INT passed as
 * argument.
 * @param n The number to write inside of the STRING.
 * @return A pointer to the STRING.
 */
char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_nbrlen(n);
	if (n == INT_MIN)
		return (ft_min());
	str = ft_setstr(n, len);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		str[i++] = (n % 10) + 48;
		n /= 10;
	}
	str[i] = n + 48;
	return (ft_swap(&str[0]));
}
