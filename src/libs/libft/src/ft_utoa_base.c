/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:47:41 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 22:20:42 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Counts the amount of digits of a SIZE_T.
 * @param n The number to count digits from.
 * @param base_len The base lenght that defines the digit size.
 * @return An INT with the amount of digits counted.
 * @note For function recicling purposes, accepts a SIZE_T base_len 
 * as argument.
 */
static int	ft_nbrlen(size_t n, size_t base_len)
{
	int	count;

	count = 1;
	while (n >= base_len)
	{
		n /= base_len;
		count++;
	}
	return (count);
}

/**
 * Creates and allocates a STRING writen with the UNSIGNED LONG INT 
 * passed as argument, following the specified base.
 * @param n The number to write inside of the STRING.
 * @param base The base in which the number must be found
 * @return A pointer to the new allocated STRING; Or NULL in case of error.
 */
char	*ft_utoa_base(size_t n, const char *base)
{
	size_t	base_len;
	size_t	i;
	char	*str;

	base_len = ft_strlen(base);
	i = ft_nbrlen(n, base_len);
	str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (n >= base_len)
	{
		str[--i] = base[n % base_len];
		n /= base_len;
	}
	str[--i] = base[n % base_len];
	return (str);
}
