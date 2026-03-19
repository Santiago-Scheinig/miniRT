/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:39:12 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/03 18:43:31 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compares two VOID pointers for n bytes.
 * @param s1 The first VOID pointer to be compared.
 * @param s2 The second VOID pointer to be compared.
 * @param n The amount of bytes to be compared.
 * @return 0 if the comparation is true; else a positive or negative INT if
 * false.
 * @note The positive or negative value returned if false is the ASCII 
 * difference between the two characters which trigger the false comparation.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_c;
	unsigned char	*s2_c;
	size_t			i;

	i = 0;
	if (!s1 || !s2)
		return (n);
	s1_c = (unsigned char *) s1;
	s2_c = (unsigned char *) s2;
	while (i < n && s1_c[i] == s2_c[i])
		i++;
	if (i == n)
		i--;
	return ((unsigned char) s1_c[i] - (unsigned char) s2_c[i]);
}
