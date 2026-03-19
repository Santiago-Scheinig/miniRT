/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iq_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:45:24 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 20:51:52 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
 * Counts the lenght of the first word on a STRING, until it reaches the 
 * divisor character or '\0'
 * @param s The STRING where to count the lenght of the first word.
 * @param c The character which divides each word.
 * @return An INT with the lenght of the word.
 * @note This function will ignore any C coincidences that happen to be inside
 * of single and double quotes (as long they open and close).
 */
static	int	ft_wrdlen(char const *s, char c)
{
	char	*tmp;
	char	quote;
	int		i;

	i = 0;
	tmp = NULL;
	while (s[i] != c && s[i])
	{
		if (s[i] == '\'')
		{
			tmp = ft_strchr(&s[i + 1], '\'');
			quote = '\'';
		}
		if (s[i] == '\"')
		{
			tmp = ft_strchr(&s[i + 1], '\"');
			quote = '\"';
		}
		if (tmp && ++i)
			while (s[i] != quote)
				i++;
		i++;
	}
	return (i);
}

/**
 * Counts the amount of words found on a STRING; a word being all the 
 * characters included between the divisor character and/or '\0'.
 * @param s The STRING where to count words.
 * @param c The character which divides each word.
 * @return An INT with the amount of words counted.
 * @note This function will ignore any C coincidences that happen to be inside
 * of single and double quotes (as long they open and close).
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
	tmp = ft_iq_strchr(s, c);
	if (tmp != NULL && tmp[1])
		count += ft_wrdcount(&tmp[1], c);
	return (count);
}

/**
 * Splits a STRING into an ARRAY of STRINGS, using a divisor character.
 * @param s The STRING to split.
 * @param c The character which divides each word.
 * @return An ARRAY of STRINGS that includes every divided word and is 
 * NULL terminated.
 * @note This function will ignore any C coincidences that happen to be inside
 * of single and double quotes (as long they open and close).
 */
char	**ft_iq_split(char const *s, char c)
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
			s = ft_iq_strchr(s, c) + 1;
		wrdstr[i] = ft_substr(s, 0, ft_wrdlen(s, c));
		if (!wrdstr[i])
			return (ft_memfree(wrdstr, i), NULL);
		s = ft_iq_strchr(s, c) + 1;
		i++;
	}
	wrdstr[i] = (void *)(0);
	return (wrdstr);
}
