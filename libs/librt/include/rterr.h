/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rterr.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:19:49 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 15:55:15 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTERR_H
# define RTERR_H
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/types.h>

/*--------------------------------------------------------------------------*/
/*----------------------------------MEMFREE---------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Frees a T_OBJECT and its associated geometry data.
 * @param content A void pointer to the T_OBJECT to free.
 * @note Designed for use with ft_lstclear as its del function. Frees
 * obj->data first if present, then the object itself. Safe to call
 * with NULL data since planes set obj->data to NULL.
 */
void	object_del(void *content);

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif