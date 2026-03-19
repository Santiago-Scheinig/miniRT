/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:32:09 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:47:08 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Reads and saves a file until EOF, specified by a file descriptor and 
 * dividing it by lines.
 * @param lines The LIST HEAD where to create new nodes for every line read.
 * @param fd The file descriptor to read from.
 * @return The amount of lines read or -1 in case of error.
 * @note A line that is just conformed by a single '\n' character isn't saved
 * and doesn't sum for the amount of lines read.
 */
int	ft_read_file(t_list **lines, int fd)
{
	t_list	*new;
	char	*str;
	int		count;

	count = 0;
	str = get_next_line(fd);
	while (str)
	{
		new = ft_lstnew(str);
		if (!new)
		{
			ft_lstclear(lines, free);
			return (-1);
		}
		ft_lstadd_back(lines, new);
		if (!(*lines))
		{
			ft_lstclear(lines, free);
			return (-1);
		}
		count++;
		str = get_next_line(fd);
	}
	return (count);
}
