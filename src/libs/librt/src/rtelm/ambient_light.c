/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:13:18 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/27 17:10:17 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

t_elem_light_a new_ambient_light(char **str)
{
	t_elem_light_a aux;

	aux.ratio = 0;
	aux.rgb = 0;
	(void) str;
	return (aux);
}