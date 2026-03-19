/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:36:37 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:02:24 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Adds a LIST node at the end of a LIST HEAD.
 * @param lst The LIST HEAD where to add the new node.
 * @param new The new LIST node to add.
 * @note If the LIST HEAD is empty, sets the new LIST node at the start
 * of it.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = ft_lstlast(*lst);
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	tmp->next = new;
}
