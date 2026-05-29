/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 17:08:16 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 19:14:54 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include "rterr.h"
#include "../.include/rtelm_private.h"

static void	build_flag(t_object *obj, char *str)
{
	if (ft_strncmp(str, "ch", 3) == 0)
		obj->material.is_checker = 1;
}

static int	build_phong(t_object *obj, char *str)
{
	char	**arr;

	arr = ft_split(str, '^');
	if (!arr)
		return (1);
	obj->material.specular.color = build_vector(arr[0]);
	obj->material.specular.exponent = ft_atod(arr[1]);
	ft_split_free(arr);
	return (0);
}

static int	build_texture(t_object *obj, char *str)
{
	t_texture	*tex;

	tex = &(obj->material.map);
	if (tex->img)
	{
		mlx_destroy_image(obj->mlx->instance, tex->img);
		tex->img = NULL;
		tex->pixels = NULL;
	}
	tex->img = mlx_xpm_file_to_image(obj->mlx->instance, str,
			&tex->width, &tex->height);
	if (!tex->img)
		return (0);
	tex->pixels = (uint32_t *)mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->pixels)
	{
		mlx_destroy_image(obj->mlx->instance, tex->img);
		tex->img = NULL;
		return (0);
	}
	return (0);
}

int	build_add_att(t_object *obj, char **arr)
{
	int	i;

	if (!obj || !arr)
		return (1);
	i = -1;
	while (arr[++i])
	{
		if (arr[i][0] == '-')
			build_flag(obj, &arr[i][1]);
		else if (arr[i][0] == 'P')
		{
			if (build_phong(obj, &arr[i][2]))
				return (1);
		}
		else if (ft_strchr(arr[i], '.'))
		{
			errno = 0;
			if (build_texture(obj, arr[i]))
				return (1);
		}
	}
	return (0);
}
