/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:54:33 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:06:35 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Frees the content of a NODE. then frees the NODE.
 * @param lst The LIST node to free.
 * @param del The function used to free the content.
 * @note In general, the del function should be free().
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst->content != NULL)
		del(lst->content);
	free(lst);
}
