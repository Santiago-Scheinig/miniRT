/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:26:08 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 22:02:56 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies size bytes from a CONST STRING src at the end of a STRING des.
 * @param dst The STRING where to copy src.
 * @param src The CONST STRING to copy from.
 * @param size The amount of bytes to be copied from src into des.
 * @return The total lenght of the STRING tried to copy, in this case,
 * the lenght of src.
 * @note - If size >= src_len + 1, it copies all of src into des.
 * @note - Else, it truncates the copy after size - 1 bytes.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size >= src_len + 1)
		ft_memmove(dst, src, src_len + 1);
	else if (size != 0)
	{
		ft_memmove(dst, src, size - 1);
		dst[size - 1] = 0;
	}
	return (src_len);
}
