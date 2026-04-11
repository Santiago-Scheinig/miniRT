/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:14:30 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 21:12:06 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

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

static void	build_camera_base(t_elem_camera *camera)
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

static void	build_camera_data(char **str, t_elem_camera *cam)
{
	char	*next;

	cam->pos.x = ft_atod(str[1]);
	next = ft_strchr(str[1], ',') + 1;
	cam->pos.y = ft_atod(next);
	next = ft_strchr(next, ',') + 1;
	cam->pos.z = ft_atod(next);
	cam->normal.x = ft_atod(str[2]);
	next = ft_strchr(str[2], ',') + 1;
	cam->normal.y = ft_atod(next);
	next = ft_strchr(next, ',') + 1;
	cam->normal.z = ft_atod(next);
	cam->fov = ft_atod(str[3]);
	cam->get_pixel_ray = &get_pixel_ray;	
}

t_elem_camera	new_camera(char **str)
{
	t_elem_camera	new_camera;

	build_camera_data(str, &new_camera);
	build_camera_base(&new_camera);
	return (new_camera);
}
