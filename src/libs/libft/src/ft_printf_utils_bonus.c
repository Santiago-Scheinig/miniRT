/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:18:53 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:10:05 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/**
 * Verifies the flags[1 - 2] and returns a new CHAR * with the expected sign
 * at the beggining.
 * - If a sign was added to str or if already had one, it sets sign to 1.
 * - Notice that when the new CHAR * is allocated, it frees the previous str
 *	 and updates it's str_len.
 */
static	char	*ft_setsign(int *flags, char *str, int *sign, int *str_len)
{
	char	*aux;

	if (!ft_isdigit(str[0]))
		*sign = 1;
	if (flags[1] && !*sign)
	{
		aux = ft_strjoin("+", str);
		if (!aux)
			return (NULL);
		*sign = 1;
		*str_len = ft_strlen(aux);
	}
	else if (flags[2] && !*sign)
	{
		aux = ft_strjoin(" ", str);
		if (!aux)
			return (NULL);
		*sign = 1;
		*str_len = ft_strlen(aux);
	}
	else
		return (str);
	free(str);
	return (aux);
}

/**
 * Adds numeric presicion to the str send as argument.
 * - Returns a new CHAR * with the expected precision parameters, detailed on
 *   flags[6], ignoring sign characters from the beggining of str.
 * - Notice that when the new CHAR * is allocated, it frees the previous str.
 */
static	char	*ft_getpsc(int *flags, int sign, char *str, int str_len)
{
	char	*pcs;
	int		pcs_len;
	int		i;

	i = -1;
	pcs_len = flags[6] + sign;
	pcs = ft_calloc(pcs_len + 1, sizeof(char));
	if (!pcs)
		return (NULL);
	ft_memset(pcs, '0', pcs_len);
	while (++i < sign)
		pcs[i] = str[i];
	ft_strlcpy(&pcs[pcs_len - str_len + sign], &str[sign], str_len + 1);
	free(str);
	return (ft_txtwth(flags, pcs, pcs_len));
}

/**
 * Verifies the flags[0 - 5] and creates a new CHAR * to meet the expected
 * parameters with the contents of str, returning it at the end.
 * - If width (flags[5]) > str_len, allocates a new CHAR * with the minimum
 *   ammount of characters to be printed, setting each of them to 'blank'.
 * - If minus (flags[0]) is true, and a new CHAR * was allocated, it pads str
 *   to the left of txt. Otherwise, it pads str to the right of txt.
 * - Notice that when the new CHAR * is allocated, it frees the previous str.
 */
char	*ft_txtwth(int *flags, char *str, int str_len)
{
	char	*txt;

	if (flags[5] > str_len && flags[7] != '%')
	{
		txt = ft_calloc(flags[5] + 1, sizeof(char));
		if (!txt)
			return (NULL);
		ft_memset(txt, ' ', flags[5]);
		if (flags[0])
			ft_memcpy(txt, str, str_len);
		else
			ft_strlcpy(&txt[flags[5] - str_len], str, str_len + 1);
	}
	else
		txt = ft_substr(str, 0, str_len);
	if (!txt)
		return (NULL);
	free(str);
	return (txt);
}

/**
 * Verifies the flags[3 - 4 - 6] for the hexadecimal specifiers: 'p' - 'x' -
 * 'X', and returns a new CHAR * to meet the expected parameters with the
 * contents of str.
 * - If numeral (flags[3]) is true and str isn't NULL, it allocates a new
 *   CHAR * that meets the expected parameters with the contents of str.
 * - If presicion (flags[6]) > str_len - sign, means str needs numeric
 *   presicion, returning ft_getpsc.
 * - If zero (flags[4]) is true, presicion (flags[6]) is false and width
 *   (flags[5]) > str_len, means str needs numeric presicion, returning
 *	 ft_getpsc.
 * - If no numeric presicion is needed or if specifier 'p', returns ft_txtwth
 *   without further verification.
 */
char	*ft_hexwth(int *flags, char *str, int str_len)
{
	char	*hex;
	int		sign;

	sign = 0;
	hex = str;
	if (flags[7] != 'p')
	{
		if (flags[3] && ft_strncmp(str, "0", 2))
		{
			hex = ft_ptrdup(str, flags[7]);
			if (!hex)
				return (NULL);
			str_len += 2;
			sign = 2;
		}
		if (flags[6] > str_len - sign)
			return (ft_getpsc(flags, sign, hex, str_len));
		else if (flags[4] && flags[6] == -1 && flags[5] > str_len)
		{
			flags[6] = flags[5] - sign;
			return (ft_getpsc(flags, sign, hex, str_len));
		}
	}
	return (ft_txtwth(flags, hex, str_len));
}

/**
 * Verifies the flags[1 - 2 - 4 - 5 - 6] for the digital specifiers: 'i' - 'd'
 * - 'u', and returns a new CHAR * to meet the expected parameters with the
 * contents of str.
 * - If str is NULL, it returns ft_txtwth with specific parameters depending
 *   on flags[1] being true or flase.
 * - Else, str it's modified by ft_setsign which verifies flags [1 - 2].
 * - If presicion (flags[6]) > str_len - sign, means str needs numeric
 *   presicion, returning ft_getpsc.
 * - If zero (flags[4]) is true, presicion (flags[6]) is false and width
 *   (flags[5]) > str_len, means str needs numeric presicion, returning
 *	 ft_getpsc.
 * - If no numeric presicion is needed, returns ft_txtwth withouth further
 *   verification.
 */
char	*ft_dgtwth(int *flags, char *str, int str_len)
{
	int		sign;

	sign = 0;
	if (!ft_strncmp(str, "0", 2) && flags[6] == 0)
	{
		free(str);
		if (flags[1])
			return (ft_txtwth(flags, ft_strdup("+"), 1));
		return (ft_txtwth(flags, ft_strdup(""), 0));
	}
	str = ft_setsign(flags, str, &sign, &str_len);
	if (!str)
		return (NULL);
	if (flags[6] > str_len - sign)
		return (ft_getpsc(flags, sign, str, str_len));
	else if (flags[4] && flags[6] == -1 && flags[5] > str_len)
	{
		flags[6] = flags[5] - sign;
		return (ft_dgtwth(flags, str, str_len));
	}
	return (ft_txtwth(flags, str, str_len));
}
