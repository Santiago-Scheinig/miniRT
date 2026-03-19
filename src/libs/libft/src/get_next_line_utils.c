/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:12:25 by root              #+#    #+#             */
/*   Updated: 2025/05/27 16:53:19 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Ft_strlend returns the count of characters on 's' until a char end, not
 * including the '\0'.
 */
size_t	ft_strlend(char *str, char end)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != 0 && str[i] != end)
		i++;
	if (!str[i] && str[i] != end)
		return (0);
	return (i);
}

/**
 * In the specific case that a bit read is not included in the ASCII table,
 * it will print an empty space instead.
 */
char	*ft_checkbin(char *line)
{
	int	c;
	int	i;

	i = -1;
	while (line[++i])
	{
		c = (int) line[i];
		if (c < 0 || c > 255)
			line[i] = ' ';
	}
	return (line);
}

void	ft_rewrite(char **txt, int line_len, int end)
{
	if ((*txt) && (*txt)[line_len])
		(*txt) = ft_calloc(end + 1, sizeof(char));
	else
		(*txt) = NULL;
}
