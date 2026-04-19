/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:13:45 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 21:17:52 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

static void	build_light_data(char **str, t_elem_light_p *light)
{
	char	*next;

	light->pos.x = ft_atod(str[1]);
	next = ft_strchr(str[1], ',') + 1;
	light->pos.y = ft_atod(next);
	next = ft_strchr(next, ',') + 1;
	light->pos.z = ft_atod(next);
	light->ratio = ft_atod(str[2]);	
}

t_elem_light_p	*new_light(char **str)
{
	t_elem_light_p	*new_light;

	new_light = ft_calloc(1, sizeof(t_elem_light_p));
	if (!new_light)
		return (NULL);
	build_light_data(str, new_light);
	return (new_light);
}
