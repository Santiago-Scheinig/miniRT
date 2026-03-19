/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:02:12 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:26:31 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Sets n bytes of a VOID pointer with a specified INT.
 * @param s The VOID pointer to set bytes into.
 * @param c The INT value to be set on each byte.
 * @param n The amount of bytes to be set on the VOID pointer.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	tmp = (unsigned char *) s;
	while (i < n)
		tmp[i++] = (unsigned char) c;
	return (s);
}
