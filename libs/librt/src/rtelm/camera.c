/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:14:30 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 19:09:22 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "rtelm_private.h"

static t_ray	get_pixel_ray(void *ptr, int x, int y)
{
	t_elem_camera	*camera;
	t_ray			ray;
	double			s;
	double			t;
	t_vector		pixel_dir;

	camera = (t_elem_camera *) ptr;
	s = (x + 0.5) / (double)SCREEN_WIDTH - 0.5;
	t = 0.5 - (y + 0.5) / (double)SCREEN_HEIGHT;
	pixel_dir = vector_sum_vector(camera->normal,
			vector_mult_scalar(camera->right, s));
	pixel_dir = vector_sum_vector(pixel_dir,
			vector_mult_scalar(camera->up, t));
	ray = ray_new(camera->pos, vector_normalize(pixel_dir));
	return (ray);
}

static void	build_camera_data(t_elem_camera *camera)
{
	t_vector	guide;
	t_vector	right_norm;
	t_vector	up_norm;
	double		v_width;

	v_width = 2.0 * tan((camera->fov / 2.0) * (M_PI / 180.0));
	guide = vector_new(0.0, 1.0, 0.0);
	if (fabs(camera->normal.y) > 1.0 - EPSILON)
		guide = vector_new(1.0, 0.0, 0.0);
	right_norm = vector_cross_product(camera->normal, guide);
	right_norm = vector_normalize(right_norm);
	up_norm = vector_cross_product(right_norm, camera->normal);
	up_norm = vector_normalize(up_norm);
	camera->right = vector_mult_scalar(right_norm, v_width);
	camera->up = vector_mult_scalar(up_norm,
			v_width * ((double)SCREEN_HEIGHT / (double)SCREEN_WIDTH));
}

int	build_camera(char **str, t_elem_camera *camera)
{
	camera->pos = build_vector(str[1]);
	camera->normal = build_vector(str[2]);
	if (!camera->normal.x && !camera->normal.y && !camera->normal.z)
		return (1);
	camera->fov = ft_atod(str[3]);
	camera->get_pixel_ray = &get_pixel_ray;	
	build_camera_data(camera);
	return (0);
}
