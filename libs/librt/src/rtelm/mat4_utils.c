/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 20:41:25 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/11 20:49:41 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"

t_mat4	cylinder_inverse_mat4(t_object *obj)
{
	t_elem_cylinder	*cy;
	t_mat4			inv;
	t_mat4			trans;
	t_mat4			rot;
	t_mat4			scale;

	cy = (t_elem_cylinder *) obj->data;
	trans = mat4_translation(cy->pos.x, cy->pos.y, cy->pos.z);
	scale = mat4_scale(cy->diam / 2.0, cy->height / 2.0, cy->diam / 2.0);
	rot = mat4_rotation(cy->normal);
	inv = mat4_inverse(mat4_mult_mat4(trans, mat4_mult_mat4(rot, scale)));
	return (inv);
}

t_mat4	plane_inverse_mat4(t_object *obj)
{
	t_elem_plane	*pl;
	t_mat4			inv;
	t_mat4			rot;
	t_mat4			trans;

	pl = (t_elem_plane *) obj->data;
	trans = mat4_translation(pl->pos.x, pl->pos.y, pl->pos.z);
	rot = mat4_rotation(pl->normal);
	inv = mat4_inverse(mat4_mult_mat4(trans, rot));
	return (inv);
}

t_mat4	sphere_inverse_mat4(t_object *obj)
{
	t_elem_sphere	*sp;
	t_mat4			inv;
	t_mat4			trans;
	t_mat4			scale;

	sp = (t_elem_sphere *) obj->data;
	trans = mat4_translation(sp->pos.x, sp->pos.y, sp->pos.z);
	scale = mat4_scale(sp->diam / 2.0, sp->diam / 2.0, sp->diam / 2.0);
	inv = mat4_inverse(mat4_mult_mat4(trans, scale));
	return (inv);
}

void	build_matrixes(t_object *new, t_mat4 (*inv_mtx)(t_object *))
{
	new->transform.inv = inv_mtx(new);
	new->transform.inv_transpose = mat4_transposed(new->transform.inv);
}
