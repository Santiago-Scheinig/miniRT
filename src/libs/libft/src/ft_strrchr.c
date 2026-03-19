/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:49:13 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 22:12:11 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for the last ocurrance of a character on a STRING.
 * @param s The STRING where to find the ocurrance.
 * @param c The character to be found.
 * @return A pointer to a position of the STRING with the last 
 * character ocurrance. If no ocurrance is found, returns NULL. 
 */
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*tmp;
	char	c_c;

	i = 0;
	c_c = (char) c;
	tmp = NULL;
	while (s[i])
	{
		if (s[i] == c_c)
			tmp = (char *) &s[i];
		i++;
	}
	if (s[i] == c_c)
		tmp = (char *) &s[i];
	return ((char *) tmp);
}
