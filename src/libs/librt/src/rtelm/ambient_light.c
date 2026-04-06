/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:13:18 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 17:20:51 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

t_elem_light_a	new_ambient_light(char **str)
{
	t_elem_light_a	aux;

	aux.ratio = ft_atod(str[1]);
	aux.rgb = ft_atod(str[2]);
	return (aux);
}
