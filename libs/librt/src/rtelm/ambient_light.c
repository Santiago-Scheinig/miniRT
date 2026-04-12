/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:13:18 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 21:15:32 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "rterr.h"

static void	build_ambient_light_data(char **str, t_elem_light_a *ambient)
{
	ambient->ratio = ft_atod(str[1]);
	ambient->rgb = ft_atod(str[2]);
}

t_elem_light_a	new_ambient_light(char **str)
{
	t_elem_light_a	new_ambient_light;

	build_ambient_light_data(str, &new_ambient_light);
	return (new_ambient_light);
}
