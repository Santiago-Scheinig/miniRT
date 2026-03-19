/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:55:26 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:16:41 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for an INT value inside of a VOID pointer for n bytes.
 * @param s The VOID pointer where to search the INT.
 * @param int The int to be searched.
 * @param n The amount of bytes to search inside of the pointer.
 * @return A VOID pointer to the first match; or NULL if no coincidence 
 * is found.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_c;
	unsigned char	c_c;
	size_t			i;

	i = 0;
	s_c = (unsigned char *) s;
	c_c = (unsigned char) c;
	while (i < n)
	{
		if (s_c[i] == c_c)
			return ((void *) &s_c[i]);
		i++;
	}
	return (NULL);
}
