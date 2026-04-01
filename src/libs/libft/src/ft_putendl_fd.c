/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:23:46 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 17:36:09 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes a STRING into a specific file descriptor.
 * @param s The STRING to be printed.
 * @param fd The file descriptor to print into.
 * @return The amount of characters printed.
 * @note After the STRING is printed, it also writes a '\n' on the file
 * descriptor.
 */
int	ft_putendl_fd(char *s, int fd)
{
	int	w_bytes;

	w_bytes = ft_putstr_fd(s, fd);
	w_bytes += ft_putchar_fd('\n', fd);
	return (w_bytes);
}
