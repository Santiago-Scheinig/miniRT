/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:33:04 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:54:41 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates and allocates a new STRING with the result of concatenate two
 * other STRINGS.
 * @param s1 The first STRING to be concatenated.
 * @param s2 The second STRING ot be concatenated.
 * @return A pointer to the new allocated STRING, resulted from the 
 * concatenation; Or NULL in case of error.
 * @note If any of the STRING to be concatenated are non-existent, it
 * returns an error.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = ft_calloc(s1_len + s2_len + 1, 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, s1_len);
	ft_strlcat(ptr, s2, s1_len + s2_len + 1);
	return (ptr);
}
