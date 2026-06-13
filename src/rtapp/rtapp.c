/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2026/06/09 18:11:39 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"
#include "rtapp_render.h"

int	rtapp_init(int argc, char **argv, t_rtapp *app)
{
	const char	*err = "initialization of miniRT app failed: %s";
	t_list		*lines;

	errno = 0;
	if (argc != 2)
		return (rtlog(RT_ERRLOG, 0, err, "invalid number of arguments."));
	lines = init_file(argv[1]);
	if (!lines)
		return (RT_FAILURE);
	if (init_file_contents(lines, argv[1], app))
		return (RT_FAILURE);
	return (RT_SUCCESS);
}

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

static void	render_worker_routine(void *arg)
{
	int		has_tiles_left;
	t_rtapp	*app;
	t_tile	tile;

	app = (t_rtapp *)arg;
	has_tiles_left = TRUE;
	while (has_tiles_left)
	{
		has_tiles_left = get_next_tile(&app->tile_queue, &tile);
		if (has_tiles_left)
			process_tile(&tile, app);
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
	app->tile_queue = new_tile_queue();
	render_worker_routine(app);
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
	del_mlx(&app->mlx, 0);
	exit(errcode);
}
