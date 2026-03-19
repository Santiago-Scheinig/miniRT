/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:21:20 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/04 14:52:04 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for the first ocurrance of a character on a STRING.
 * @param s The STRING where to find the ocurrance.
 * @param c The character to be found.
 * @return A pointer to a position of the STRING with the first 
 * character ocurrance. If no ocurrance is found, returns NULL. 
 */
char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	c_c;

	if (!s)
		return (NULL);
	i = 0;
	c_c = (char) c;
	while (s[i])
	{
		if (s[i] == c_c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == c_c)
		return ((char *) &s[i]);
	return (NULL);
}
