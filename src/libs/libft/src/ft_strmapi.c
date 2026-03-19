/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:07:52 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 22:06:14 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates and allocates a new STRING with the result of iterate a 
 * FUNCTION on every character of a CONST STRING.
 * @param s The CONST STRING to be iterated.
 * @param f The FUNCTION to be iterated on every character of the
 * CONST STRING.
 * @return A pointer to the new allocated STRING with the results of
 * all the iterations in order; Or NULL in case of error.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	str = ft_calloc(len + 1, 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	return (str);
}
