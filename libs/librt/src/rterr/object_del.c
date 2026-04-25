/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:55:26 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/23 20:52:38 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rterr.h"

void	object_del(void *content)
{
	t_object	*aux;

	aux = content;
	if (aux->data)
		free(aux->data);
	free(aux);
}
