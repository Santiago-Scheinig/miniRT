/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iq_strchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:15:28 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 20:54:21 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for the first ocurrance of a character on a STRING.
 * @param s The STRING where to find the ocurrance.
 * @param c The character to be found.
 * @return A pointer to a position of the STRING with the first 
 * character ocurrance. If no ocurrance is found, returns NULL. 
 * @note This function will ignore any C coincidences that happen 
 * to be inside of single and double quotes (as long they open and close).
 */
char	*ft_iq_strchr(char const *s, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\'' && s[i + 1])
			tmp = ft_strchr(&s[i + 1], '\'');
		if (s[i] == '\"' && s[i + 1])
			tmp = ft_strchr(&s[i + 1], '\"');
		if (tmp)
		{
			s = tmp;
			i = 0;
			tmp = NULL;
		}
		i++;
	}
	if (!s[i])
		return (NULL);
	return ((char *) &s[i]);
}
