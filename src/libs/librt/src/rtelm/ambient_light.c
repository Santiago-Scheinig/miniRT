/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:13:18 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/02 14:54:32 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

t_elem_light_a	new_ambient_light(char **str)
{
	t_elem_light_a	aux;

	aux.ratio = 0;
	aux.rgb = 0;
	(void) str;
	return (aux);
}
