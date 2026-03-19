/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:32:51 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:25:12 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Moves n bytes from a src VOID pointer into a dest VOID pointer.
 * @param dest The VOID pointer where to move bytes into.
 * @param src The VOID pointer where to move bytes from.
 * @param n The amount of bytes to be moved.
 * @return The VOID pointer to dest.
 * @note This function modifies the dest VOID pointer and, additionally,
 * checks if the memory position of src is close to dest to avoid loosing
 * information during the movement.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;
	size_t			i;

	i = 0;
	if (!dest && !src)
		return (dest);
	src_tmp = (unsigned char *) src;
	dst_tmp = (unsigned char *) dest;
	if (dst_tmp > src_tmp)
	{
		while (n > i)
		{
			n--;
			dst_tmp[n] = src_tmp[n];
		}
	}
	while (i < n)
	{
		dst_tmp[i] = src_tmp[i];
		i++;
	}
	return (dest);
}
