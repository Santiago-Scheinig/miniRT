/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:43:41 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/03 21:10:01 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_istrim(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

/**
 * Creates and allocates a new STRING resultant of the trimming of a 
 * CONST STRING set in a CONST STRING s1.
 * @param s1 The CONST STRING to be compared for trimming.
 * @param set The character base to be trimmed.
 * @return A pointer to the new STRING resultant of the trimming.
 * @note - Cuts every match of 'set' from the start of 's1' until a non match.
 * @note - Cuts every match of 'set' from the end of 's1' until a non match.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tmp;
	int		s1_len;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_istrim(s1[i], set))
		i++;
	s1_len = ft_strlen(&s1[i]);
	if (s1_len == 0)
		return (ft_strdup(""));
	while (ft_istrim(s1[s1_len + i - 1], set))
		s1_len--;
	tmp = ft_calloc(s1_len + 1, 1);
	if (!tmp)
		return (NULL);
	ft_strlcat(tmp, &s1[i], s1_len + 1);
	return (tmp);
}
