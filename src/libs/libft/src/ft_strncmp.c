/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:58:18 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 22:08:07 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compares two CONST STRING for n bytes.
 * @param s1 The first CONST STRING to be compared.
 * @param s2 The second CONST STRING to be compared.
 * @param n The amount of bytes to be compared,
 * @return 0 if the comparation is true; else a positive or negative INT if
 * false.
 * @note The positive or negative value returned if false is the ASCII 
 * difference between the two characters which trigger the false comparation.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (i == n)
		i--;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
