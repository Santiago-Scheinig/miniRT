/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_bonus_types.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:00:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/29 00:00:00 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_BONUS_TYPES_H
# define RTAPP_BONUS_TYPES_H

# if BONUS
#  include <pthread.h>
#  define WORKER_COUNT 16

typedef struct s_rtapp_bonus
{
	t_rtlog			logfd;
	pthread_t		workers[WORKER_COUNT];
	pthread_mutex_t	queue_mutex;
}	t_rtapp_bonus;

# else

typedef struct s_rtapp_bonus
{
	int	_pad;
}	t_rtapp_bonus;

# endif

#endif