/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:55:26 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/11 19:03:25 by sscheini         ###   ########.fr       */
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