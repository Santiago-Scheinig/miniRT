/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:49:41 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:50:42 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Counts the amount of words found on a STRING; a word being all the 
 * characters included between the divisor character and/or '\0'.
 * @param s The STRING where to count words.
 * @param c The character which divides each word.
 * @return An INT with the amount of words counted.
 */
static	int	ft_wrdcount(char const *s, char c)
{
	char	*tmp;
	int		count;

	count = 0;
	if (c == 0)
		return (1);
	if (s[0] == 0)
		return (0);
	if (s[0] != c)
		count++;
	tmp = ft_strchr(s, c);
	if (tmp != NULL && tmp[1])
		count += ft_wrdcount(&tmp[1], c);
	return (count);
}

/**
 * Counts the lenght of the first word on a STRING, until it reaches the 
 * divisor character or '\0'
 * @param s The STRING where to count the lenght of the first word.
 * @param c The character which divides each word.
 * @return An INT with the lenght of the word.
 */
static	int	ft_wrdlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

/**
 * Frees every pointer on an ARRAY of STRINGS and the ARRAY pointer, even
 * if it's not NULL terminated.
 * @param wrdstr The ARRAY of STRINGS to free.
 * @param index The amount of STRINGS to free inside of the array.
 */
static	void	ft_memfree(char **wrdstr, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(wrdstr[i]);
		i++;
	}
	free(wrdstr);
}

/**
 * Splits a STRING into an ARRAY of STRINGS, using a divisor character.
 * @param s The STRING to split.
 * @param c The character which divides each word.
 * @return An ARRAY of STRINGS that includes every divided word and is 
 * NULL terminated.
 */
char	**ft_split(char const *s, char c)
{
	char	**wrdstr;
	int		w;
	int		i;

	if (!s)
		return (NULL);
	if (s[0] == 0)
		return (ft_calloc(1, sizeof(char *)));
	i = 0;
	w = ft_wrdcount(s, c);
	wrdstr = (char **) malloc((w + 1) * sizeof(char *));
	if (!wrdstr)
		return (NULL);
	while (i < w)
	{
		while (s[0] == c)
			s = ft_strchr(s, c) + 1;
		wrdstr[i] = ft_substr(s, 0, ft_wrdlen(s, c));
		if (!wrdstr[i])
			return (ft_memfree(wrdstr, i), NULL);
		s = ft_strchr(s, c) + 1;
		i++;
	}
	wrdstr[i] = (void *)(0);
	return (wrdstr);
}
