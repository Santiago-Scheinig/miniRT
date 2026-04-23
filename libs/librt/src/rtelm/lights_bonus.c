/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:47:37 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/23 20:51:18 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "rtelm_private.h"

t_elem_light_a	build_la(char **str)
{
	t_elem_light_a	new_la;

	new_la->ratio = ft_atod(str[1]);
	new_la->color = build_color(str[2]);
	return (new_la);
}

t_elem_light_p	*build_lp(char **str)
{
	t_elem_light_p	*new_lp;
	char			*next;

	new_lp = ft_calloc(1, sizeof(t_elem_light_p));
	if (!new_lp)
		return (NULL);
	new_lp->pos.x = ft_atod(str[1]);
	next = ft_strchr(str[1], ',') + 1;
	new_lp->pos.y = ft_atod(next);
	next = ft_strchr(next, ',') + 1;
	new_lp->pos.z = ft_atod(next);
	new_lp->ratio = ft_atod(str[2]);
	new_lp->color = build_color(str[3]);
	return (new_lp);
}
