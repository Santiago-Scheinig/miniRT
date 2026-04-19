/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:10:37 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 17:36:08 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes a character into a specific file descriptor.
 * @param c The character to be printed.
 * @param fd The file descriptor to print into.
 * @return The amount of characters printed.
 */
int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
