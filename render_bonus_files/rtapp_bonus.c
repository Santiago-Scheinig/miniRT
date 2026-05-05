/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 16:11:08 by aramos-r          #+#    #+#             */
/*   Updated: 2026/05/05 17:35:41 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_bonus.h"

static void	process_tile(t_tile *tile, t_rtapp *app)
{
	int				x;
	int				y;
	t_vector		color;
	t_hit			hit;
	t_ray			ray;

	x = tile->x_start;
	y = tile->y_start;
	while (y < tile->y_end)
	{
		while (x < tile->x_end)
		{
			ray = app->camera.get_pixel_ray(&app->camera, x, y);
			hit = get_hit_from_ray(ray, app->objects);
			if (hit.obj)
				color = get_color_at_hit(hit, app->objects, app);
			else
				color = vector_new(0, 0, 0);
			*(tile->get_pixel_ptr(app->img, x, y)) = translate_color(color);
			x++;
		}
		x = tile->x_start;
		y++;
	}
}

static void	*render_worker_routine(void *arg)
{
	int		has_tiles_left;
	t_rtapp	*app;
	t_tile	tile;

	app = (t_rtapp *)arg;
	has_tiles_left = TRUE;
	while (has_tiles_left)
	{
		pthread_mutex_lock(&app->queue_mutex);
		has_tiles_left = get_next_tile(&app->tile_queue, &tile);
		pthread_mutex_unlock(&app->queue_mutex);
		if (has_tiles_left)
			process_tile(&tile, app);
	}
	return (NULL);
}

static void	wait_created_workers(t_rtapp *app, int worker_count)
{
	int	i;

	i = 0;
	while (i < worker_count)
	{
		pthread_join(app->workers[i], NULL);
		i++;
	}
}

/**
 * Runs the miniRT redering loop.
 * @param app The initialized T_RTAPP instance.
 * @return RT_SUCCESS on clean exit, RT_FAILURE on error.
 * @todo Implement once tile rendering and parsing and img initalization
 * are complete.
 * @note Pseudocode plan: ?.
 */
int	rtapp_render(t_rtapp *app)
{
	int	i;

	app->tile_queue = new_tile_queue();
	if (pthread_mutex_init(&app->queue_mutex, NULL) != 0)
		return (RT_FAILURE);
	i = 0;
	while (i < WORKER_COUNT)
	{
		if (pthread_create(&(app->workers[i]),
			NULL, render_worker_routine, app) != 0)
			{
				wait_created_workers(app, i - 1);
				pthread_mutex_destroy(&app->queue_mutex);
				return (RT_FAILURE);
			}
		i++;
	}
	wait_created_workers(app, WORKER_COUNT);
	pthread_mutex_destroy(&app->queue_mutex);
	return (RT_SUCCESS);
}

int	rtapp_kill(t_rtapp *app, t_rterr errcode)
{
	if (app->objects)
		ft_lstclear(&(app->objects), object_del);
	if (app->lights)
		ft_lstclear(&(app->lights), free);
	if (app->img)
		free(app->img);
	exit(errcode);
}
