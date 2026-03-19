/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:16:10 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 22:00:32 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Concatenates size bytes from a CONST STRING src at the end of a STRING des.
 * @param dst The STRING where to concatenate src.
 * @param src The CONST STRING to be concatenated into des.
 * @param size The amount of bytes to be concatenated from src into des.
 * @return The total lenght of the STRING tried to concatenate, in this case,
 * the initial lenght of des plus the lenght of src.
 * @note - If size <= dst_len, it doesn't concatenate.
 * @note - If size >= dst_len + src_len + 1, it concatenates all of src.
 * @note - Else, it truncates the concatenation after size - 1 bytes.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size >= dst_len + src_len + 1)
		ft_memmove(&dst[dst_len], src, src_len + 1);
	else if (size != 0 && size > dst_len + 1)
	{
		ft_memmove(&dst[dst_len], src, size - dst_len - 1);
		dst[size - 1] = '\0';
	}
	else if (size <= dst_len)
		return (size + src_len);
	return (dst_len + src_len);
}
