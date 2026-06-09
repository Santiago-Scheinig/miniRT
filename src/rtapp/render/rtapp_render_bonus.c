/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_render_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:00:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/29 00:00:00 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_render_bonus.h"

static void	process_tile(t_tile *tile, t_rtapp *app)
{
	int			x;
	int			y;
	t_vector	color;
	t_hit		hit;

	y = tile->y_start;
	while (y < tile->y_end)
	{
		x = tile->x_start;
		while (x < tile->x_end)
		{
			hit = get_hit_from_ray(
					app->camera.get_pixel_ray(&app->camera, x, y),
					app->objects);
			if (hit.obj)
				color = get_color_at_hit(hit, app->objects, app);
			else
				color = vector_new(0, 0, 0);
			*(tile->get_pixel_ptr(app->img, x, y)) = translate_color(color);
			x++;
		}
		y++;
	}
}

static void	*render_worker_routine(void *arg)
{
	int			has_tiles;
	t_rtapp		*app;
	t_tile		tile;

	app = (t_rtapp *)arg;
	has_tiles = TRUE;
	while (has_tiles)
	{
		pthread_mutex_lock(&app->bonus.queue_mutex);
		has_tiles = get_next_tile(&app->tile_queue, &tile);
		pthread_mutex_unlock(&app->bonus.queue_mutex);
		if (has_tiles)
			process_tile(&tile, app);
	}
	return (NULL);
}

static void	wait_workers(t_rtapp *app, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(app->bonus.workers[i], NULL);
		i++;
	}
}

int	rtapp_render(t_rtapp *app)
{
	int	i;

	app->tile_queue = new_tile_queue();
	if (pthread_mutex_init(&app->bonus.queue_mutex, NULL) != 0)
		return (RT_FAILURE);
	i = 0;
	while (i < WORKER_COUNT)
	{
		if (pthread_create(&(app->bonus.workers[i]),
				NULL, render_worker_routine, app) != 0)
		{
			wait_workers(app, i);
			pthread_mutex_destroy(&app->bonus.queue_mutex);
			return (RT_FAILURE);
		}
		i++;
	}
	wait_workers(app, WORKER_COUNT);
	pthread_mutex_destroy(&app->bonus.queue_mutex);
	return (RT_SUCCESS);
}
