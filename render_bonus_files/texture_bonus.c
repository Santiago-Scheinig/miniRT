/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:00:00 by aramos-r          #+#    #+#             */
/*   Updated: 2026/05/04 23:03:04 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_bonus.h"

#define CHECKER_SCALE 4.0

t_uv	sphere_uv(t_vector local_point)
{
	t_uv	uv;

	uv.u = atan2(local_point.z, local_point.x) / (2.0 * M_PI) + 0.5;
	uv.v = asin(local_point.y) / M_PI + 0.5;
	return (uv);
}

t_uv	cylinder_uv(t_vector local_point)
{
	t_uv	uv;

	uv.u = atan2(local_point.z, local_point.x) / (2.0 * M_PI) + 0.5;
	uv.v = (local_point.y + 1.0) / 2.0;
	return (uv);
}

t_uv	cone_uv(t_vector local_point)
{
	t_uv	uv;

	uv.u = atan2(local_point.z, local_point.x) / (2.0 * M_PI) + 0.5;
	uv.v = local_point.y;
	return (uv);
}

t_uv	plane_uv(t_vector local_point)
{
	t_uv	uv;

	uv.u = local_point.x;
	uv.v = local_point.z;
	return (uv);
}

t_uv	paraboloid_uv(t_vector local_point)
{
	t_uv	uv;

	uv.u = atan2(local_point.z, local_point.x) / (2.0 * M_PI) + 0.5;
	uv.v = local_point.y;
	return (uv);
}

t_uv	hyperboloid_uv(t_vector local_point)
{
	t_uv	uv;

	uv.u = atan2(local_point.z, local_point.x) / (2.0 * M_PI) + 0.5;
	uv.v = (local_point.y + 1.0) / 2.0;
	return (uv);
}

t_vector	get_checker_color(t_uv uv)
{
	int	iu;
	int	iv;

	iu = (int)floor(uv.u * CHECKER_SCALE);
	iv = (int)floor(uv.v * CHECKER_SCALE);
	if ((iu + iv) % 2 == 0)
		return (vector_new(1.0, 1.0, 1.0));
	return (vector_new(0.0, 0.0, 0.0));
}
