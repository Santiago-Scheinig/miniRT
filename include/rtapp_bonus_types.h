/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_bonus_types.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:27:12 by aramos-r          #+#    #+#             */
/*   Updated: 2026/06/15 16:27:13 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_BONUS_TYPES_H
# define RTAPP_BONUS_TYPES_H

# include "rtapp.h"
# include <pthread.h>
# define WORKER_COUNT 16

typedef struct s_tile
{
	int			x_start;
	int			y_start;
	int			x_end;
	int			y_end;
	uint32_t	*(*get_pixel_ptr)(uint32_t *img, int x, int y);
}	t_tile;

typedef struct s_tile_queue
{
	int	current_x;
	int	current_y;
}	t_tile_queue;

typedef struct s_rtapp_bonus
{
	t_rtlog			logfd;
	pthread_t		workers[WORKER_COUNT];
	pthread_mutex_t	queue_mutex;
}	t_rtapp_bonus;

typedef struct s_rtapp
{
	uint32_t		*img;
	t_list			*objects;
	t_list			*lights;
	t_mlx			mlx;
	t_elem_camera	camera;
	t_elem_light_a	ambient;
	t_tile_queue	tile_queue;
	t_rtapp_bonus	bonus;
}	t_rtapp;

#endif