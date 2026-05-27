/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:13:45 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 17:39:26 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "../.include/rtelm_private.h"

t_elem_light_a	build_la(char **str)
{
	t_elem_light_a	new_la;

	new_la.ratio = ft_atod(str[1]);
	new_la.color = build_color(str[2]);
	return (new_la);
}

t_elem_light_p	*build_lp(char **str)
{
	t_elem_light_p	*new_lp;

	new_lp = ft_calloc(1, sizeof(t_elem_light_p));
	if (!new_lp)
		return (NULL);
	new_lp->pos = build_vector(str[1]);
	new_lp->ratio = ft_atod(str[2]);
	return (new_lp);
}
