/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:24:31 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:51:50 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates and allocates a STRING that includes all the characters of a CONST
 * STRING.
 * @param s The CONST STRING to allocate.
 * @return A pointer to the new allocated STRING.
 */
char	*ft_strdup(const char *s)
{
	char	*str;
	int		str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	str = malloc(str_len + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, str_len + 1);
	ft_memcpy(str, s, str_len);
	return (str);
}
