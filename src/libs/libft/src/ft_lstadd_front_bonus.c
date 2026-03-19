/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:59:50 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:03:52 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Adds a LIST node at the start of a LIST HEAD.
 * @param lst The LIST HEAD where to add the new node.
 * @param new The new LIST node to add.
 * @note The previous node at the start of the LIST HEAD is set
 * as the next node of the new LIST HEAD.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = lst[0];
	lst[0] = new;
}
