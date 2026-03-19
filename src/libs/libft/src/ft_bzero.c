/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:37:34 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 20:39:11 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Erases the data in the n bytes of the memory starting at the location
 * pointed to by s, by writing zeros (bytes containing '\0') to that area.
 * @param s The pointer location where to rewrite.
 * @param n The amount of bytes to rewrite.
 */
void	ft_bzero(void *s, size_t n)
{
	if (n != 0)
		ft_memset(s, '\0', n);
}
