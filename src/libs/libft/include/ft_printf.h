/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:44:05 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/22 18:22:29 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>

/**
 * Creates and returns a CONST CHAR * that includes an hexadecimal base
 * wich variates on dependence to the specifier send as an argument.
 */
const char	*ft_sethexa(int specifier);

/**
 * Performs the same way as ft_strdup, but for a single CHAR argument.
 */
char		*ft_chrdup(char c);

/**
 * Allocates a new CHAR * adding "0x" to the ptr send as argument.
 * - Notice that it frees the previous ptr before returning the new one.
 */
char		*ft_ptrdup(void *ptr, int spf);

/**
 * Writes the formatted output to stdout.
 */
int			ft_printf(char const *txt, ...);

/**
 * Writes the formatted output to the fd specified as argument.
 */
int			ft_printfd(int fd, char const *txt, ...);

/**
 * Writes the formatted output to the fd specified as argument.
 * It recieves a va_list instead of creating one.
 */
int			ft_vprintfd(int fd, char const *s, va_list args);

#endif