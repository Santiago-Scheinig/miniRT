/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/21 19:44:52 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"
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


/**
 * Runs the miniRT redering loop.
 * @param app The initialized T_RTAPP instance.
 * @return RT_SUCCESS on clean exit, RT_FAILURE on error.
 * @todo Implement once tile rendering and parsing and img initalization
 * are complete.
 * @note Pseudocode plan: ?.
 */
int rtapp_render(t_rtapp *app)
{
	t_tile_queue	queue;
	t_tile			tile;
	uint32_t		*pixel;
	t_vector		color;
	t_hit			hit;
	t_ray			ray;
	int x;
	int y;

	int counter = 0;
	int total = (SCREEN_WIDTH) * (SCREEN_HEIGHT);
	queue = new_tile_queue();
	while (get_next_tile(&queue, &tile))
	{
		x = tile.x_start;
		y = tile.y_start;
		while (y < tile.y_end)
		{
			while (x < tile.x_end)
			{
				printf("pixel (%d, %d)\n", counter++, total);
				pixel = tile.get_pixel_ptr(app->img, x, y);
				ray = app->camera.get_pixel_ray(&app->camera, x, y);
				hit = get_hit_from_ray(ray, app->objects);
				if (hit.obj)
				{
					color = get_color_at_hit(hit, app->objects, app);
					// printf("hit at (%f, %f, %f) with normal (%f, %f, %f)\n",
					// 	hit.pos.x, hit.pos.y, hit.pos.z,
					// 	hit.surf_normal.x, hit.surf_normal.y, hit.surf_normal.z);
				}
				else
					color = vector_new(0, 0, 0);
				*pixel = translate_color(color);
				x++;
			}
			x = tile.x_start;
			y++;
		}
	}
	return (RT_SUCCESS);
}

int rtapp_kill(t_rtapp *app, t_rterr errcode)
{
	if (app->objects)
		ft_lstclear(&(app->objects), object_del);
	if (app->lights)
		ft_lstclear(&(app->lights), free);
	if (app->img)
		free(app->img);
	exit(errcode);
}