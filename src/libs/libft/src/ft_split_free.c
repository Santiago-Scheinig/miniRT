/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:58:41 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:48:17 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Frees an ARRAY of STRINGS, usually allocated by ft_split().
 * @param split The ARRAY of STRINGS to free.
 */
void	*ft_split_free(char **split)
{
	int	i;

	i = -1;
	if (split)
	{
		while (split[++i])
			free(split[i]);
		free(split);
	}
	return (NULL);
}
