/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:01:21 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:10:36 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * Creates and returns a CONST CHAR * that includes an hexadecimal base
 * wich variates on dependence to the specifier send as an argument.
 */
const char	*ft_sethexa(int specifier)
{
	const char	*hex_base;

	hex_base = NULL;
	if (specifier == 'x' || specifier == 'p')
		hex_base = "0123456789abcdef";
	if (specifier == 'X')
		hex_base = "0123456789ABCDEF";
	return (hex_base);
}

/**
 * Allocates a new CHAR * adding "0x" to the ptr send as argument.
 * - Notice that it frees the previous ptr before returning the new one.
 */
char	*ft_ptrdup(void *ptr, int spf)
{
	char	*aux;

	if (spf == 'X')
		aux = ft_strjoin("0X", ptr);
	else
		aux = ft_strjoin("0x", ptr);
	free(ptr);
	return (aux);
}

/**
 * Performs the same way as ft_strdup, but for a single CHAR argument.
 */
char	*ft_chrdup(char c)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	if (!str)
		return (NULL);
	*str = c;
	return (str);
}
