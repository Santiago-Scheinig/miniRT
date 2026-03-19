/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:51:56 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:12:48 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates and allocates a new LIST result of iterating a FUNCTION on every
 * content of the original LIST.
 * @param lst The starting node to start iterating.
 * @param f The FUNCTION to iterate on every content.
 * @param del The FUNCTION used to free each content in case of error.
 * @return A pointer to the start of the new allocated LIST; or NULL in case
 * of error.
 * @note If any node creation fails, frees every other previous iteration
 * using the del FUNCTION on every content. Usually being free().
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp_lst;
	t_list	*tmp_node;
	void	*cont;

	tmp_lst = NULL;
	if (!lst || !f || !del)
		return (tmp_lst);
	while (lst)
	{
		cont = f(lst->content);
		if (!cont)
			return (ft_lstclear(&tmp_lst, del), NULL);
		tmp_node = ft_lstnew(cont);
		if (!tmp_node)
			return (del(cont), ft_lstclear(&tmp_lst, del), NULL);
		ft_lstadd_back(&tmp_lst, tmp_node);
		lst = lst->next;
	}
	return (tmp_lst);
}
