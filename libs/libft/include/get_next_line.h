/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:11:26 by root              #+#    #+#             */
/*   Updated: 2025/05/27 16:46:21 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# include "libft.h"
# include "errno.h"

/**
 * Ft_strlend returns the count of characters on 's' until a char end, not
 * including the '\0'.
 */
size_t	ft_strlend(char *str, char end);

/**
 * Ft_rewrite, reallocates inside of txt the amount of extra characters
 * from the first jump line fouded. Allowing to rewrite the remaining text.
 * @note If there's no extra characters, sets *txt to NULL.
 */
void	ft_rewrite(char **txt, int line_len, int end);

/**
 * In the specific case that a bit read is not included in the ASCII table,
 * it will print an empty space instead.
 */
char	*ft_checkbin(char *line);

/**
 * Returns a char * with the next line on the file descriptor given.
 */
char	*get_next_line(int fd);

#endif