/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtfree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:55:26 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/27 17:12:35 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rterr.h"

void	rtfree(void *content)
{
	t_object	*aux;

	aux = content;
	if (aux->data)
		free(aux->data);
}