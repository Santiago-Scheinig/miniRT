/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:18:11 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 16:49:49 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H
# include "libft.h"

/**
 * Used to saved the information needed to print str with its detailed flags.
 */
typedef struct s_print
{
	int		*flags;
	char	*str;
}	t_print;

/**
 * Creates an INT * that saves the flags information.
 * - Each position of flags represents a different flag or value assigned.
 * - The following flags are represented with true or false:
 * | [0] -> '-' | [1] -> '+' | [2] -> 'blank' | [3] -> '#' | [4] -> '0' |
 * - Width is set to 0 in position [5], unless a witdh value is detailed.
 * - Presicion is set to -1 in position [6], unless '.' is called.
 * - The specifier character is detailed in position [7] as ascci value.
 * | [5] -> Width | [6] -> Presicion | [7] -> Specifier |
 * - If the flag format isn't valid, returns NULL.
 */
int		*ft_flagdescriptor(const char *s);

/**
 * Verifies the flags[0 - 5] and creates a new CHAR * to meet the expected
 * parameters with the contents of str, returning it at the end.
 * - If width (flags[5]) > str_len, allocates a new CHAR * with the minimum
 *   ammount of characters to be printed, setting each of them to 'space'.
 * - If minus (flags[0]) is true, and a new CHAR * was allocated, it pads str
 *   to the left of txt. Otherwise, it pads str to the right.
 * - Notice that when the new CHAR * is allocated, it frees the previous str.
 */
char	*ft_txtwth(int *flags, char *str, int str_len);

/**
 * Verifies the flags[1 - 2 - 4 - 5 - 6] for the digital specifiers: 'i' - 'd'
 * - 'u', and returns a new CHAR * to meet the expected parameters with the
 * contents of str.
 * - If str is NULL, it returns ft_txtwth with specific parameters depending
 *   on plus flags[1] being true or flase.
 * - Else, str it's modified by ft_setsign which verifies flags [1 - 2].
 * - If presicion (flags[6]) > str_len - sign, means str needs numeric
 *   presicion, returning ft_getpsc.
 * - If zero (flags[4]) is true, presicion (flags[6]) is false and width
 *   (flags[5]) > str_len, means str needs numeric presicion, returning
 *	 ft_getpsc.
 * - If no numeric presicion is needed, returns ft_txtwth withouth further
 *   verification.
 */
char	*ft_dgtwth(int *flags, char *str, int str_len);

/**
 * Verifies the flags[3 - 4 - 6] for the hexadecimal specifiers: 'p' - 'x' -
 * 'X', and returns a new CHAR * to meet the expected parameters with the
 * contents of str.
 * - If numeral (flags[3]) is true and str isn't NULL, it allocates a new
 *   CHAR * that meets the expected parameters with the contents of str.
 * - If presicion (flags[6]) > str_len - sign, means str needs numeric
 *   presicion, returning ft_getpsc
 * - If zero (flags[4]) is true, presicion (flags[6]) is false and width
 *   (flags[5]) > str_len, means str needs numeric presicion, returning
 *	 ft_getpsc.
 * - If no numeric presicion is needed or if specifier 'p', returns ft_txtwth
 *   without further verification.
 */
char	*ft_hexwth(int *flags, char *str, int str_len);

#endif