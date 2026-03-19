/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:54:48 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:22:55 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies n bytes from a src VOID pointer into a dest VOID pointer.
 * @param dest The VOID pointer where to copy bytes into.
 * @param src The VOID pointer where to copy bytes from.
 * @param n The amount of bytes to be copied.
 * @return The VOID pointer to dest.
 * @note This function modifies the dest VOID pointer.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!src && !dest)
		return (dest);
	ft_memmove(dest, src, n);
	return (dest);
}
