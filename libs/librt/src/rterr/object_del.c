/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 18:09:13 by sscheini          #+#    #+#             */
/*   Updated: 2026/06/09 18:09:23 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

void	object_del(void *content)
{
	t_object	*aux;

	aux = content;
	if (aux->data)
		free(aux->data);
	free(aux);
}
