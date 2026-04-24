/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 19:01:10 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/24 13:51:31 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmlx.h"

static int	close_window(void *param)
{
	mlx_loop_end(((t_mlx *)param)->instance);
	return (0);
}

static int	on_keypress(int keycode, void *param)
{
	if (keycode == 65307)
		return (close_window(param));
	return (0);
}

static void	set_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1L << 0, &on_keypress, mlx);
	mlx_hook(mlx->win, 17, 0, &close_window, mlx);
}

static int	del_mlx(t_mlx *mlx, int exit_no)
{
	if (mlx->img)
		mlx_destroy_image(mlx->instance, mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->instance, mlx->win);
	if (mlx->instance)
	{
		mlx_destroy_display(mlx->instance);
		free(mlx->instance);
	}
	free(mlx);
	return (exit_no);
}

int	window_run(uint32_t *image, char *filename)
{
	char		*w;
	t_mlx		*mlx;

	w = ft_strjoin("miniRT - ", filename);
	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return (1);
	mlx->instance = mlx_init();
	if (!mlx->instance)
		return (del_mlx(mlx, 1));
	mlx->win = mlx_new_window(mlx->instance, SCREEN_WIDTH, SCREEN_HEIGHT, (char *) w);
	free(w);
	if (!mlx->win)
		return (del_mlx(mlx, 1));
	mlx->img = mlx_new_image(mlx->instance, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!mlx->img)
		return (del_mlx(mlx, 1));
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len, &mlx->endian);
	if (mlx->bpp != 32 || mlx->line_len != SCREEN_WIDTH * 4)
		return (del_mlx(mlx, 1));
	ft_memcpy(mlx->addr, image, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint32_t));
	mlx_put_image_to_window(mlx->instance, mlx->win, mlx->img, 0, 0);
	set_hooks(mlx);
	mlx_loop(mlx->instance);
	return (del_mlx(mlx, 0));
}
