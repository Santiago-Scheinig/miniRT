/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:48:27 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/03 18:40:07 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for the first match of all of a CONST STRING little in a 
 * CONST STRING big for len bytes.
 * @param big The large CONST STRING to find the match.
 * @param small The small CONST STRING to be matched on big.
 * @param len The amount of bytes to search on big.
 * @return A pointer to the CONST STRING where the full first match
 * was found; Or NULL if no match where found or big doesn't exists.
 * @note - The match musst exist in len bytes of big.
 * @note - Returns big if little is empty.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		little_len;

	if (!big)
		return (NULL);
	little_len = ft_strlen(little);
	if (!little_len)
		return ((char *) big);
	i = 0;
	while (i < len)
	{
		if (!big[i])
			return (NULL);
		if (big[i] == little[0] && len >= little_len + i)
		{
			if (ft_strncmp(&big[i], &little[0], little_len) == 0)
				return ((char *) &big[i]);
		}
		i++;
	}
	return (NULL);
}
