/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:49:41 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 17:36:13 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_invalid(char	c, char	*c_str)
{
	int	i;
	int	ans;

	i = -1;
	ans = 0;
	while (c_str[++i])
		if (c == c_str[i])
			ans = 1;
	if (ans)
		return (1);
	return (0);
}

/**
 * Counts the amount of words found on a STRING; a word being all the 
 * characters included between the divisor character and/or '\0'.
 * @param s The STRING where to count words.
 * @param c The character which divides each word.
 * @return An INT with the amount of words counted.
 */
static int ft_wrdcount(char const *s, char *c_str)
{
    int count = 0;

    while (*s)
    {
        while (*s && is_invalid(*s, c_str))
            s++;
        if (*s)
            count++;
        while (*s && !is_invalid(*s, c_str))
            s++;
    }
    return count;
}

/**
 * Counts the lenght of the first word on a STRING, until it reaches the 
 * divisor character or '\0'
 * @param s The STRING where to count the lenght of the first word.
 * @param c The character which divides each word.
 * @return An INT with the lenght of the word.
 */
static int ft_wrdlen(char const *s, char *c_str)
{
    int i = 0;

    while (s[i] && !is_invalid(s[i], c_str))
        i++;
    return i;
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
 * Splits a STRING into an ARRAY of STRINGS, using an array of 
 * divisor characters.
 * @param s The STRING to split.
 * @param c_str The array of characters which divides each word.
 * @return An ARRAY of STRINGS that includes every divided word and is 
 * NULL terminated.
 */
char	**ft_split_base(char const *s, char *c_str)
{
	char	**wrdstr;
	int		w;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if (s[0] == 0)
		return (ft_calloc(1, sizeof(char *)));
	i = -1;
	w = ft_wrdcount(s, c_str);
	wrdstr = (char **) malloc((w + 1) * sizeof(char *));
	if (!wrdstr)
		return (NULL);
	while (++i < w)
	{
		j = -1;
		while (s[0] && is_invalid(s[0], c_str))
			s++;
		wrdstr[i] = ft_substr(s, 0, ft_wrdlen(s, c_str));
		if (!wrdstr[i])
			return (ft_memfree(wrdstr, i), NULL);
		while (s[0] && !is_invalid(s[0], c_str))
			s++;
	}
	wrdstr[i] = (void *)(0);
	return (wrdstr);
}
