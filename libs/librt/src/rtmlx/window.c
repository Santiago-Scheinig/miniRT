/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 19:01:10 by sscheini          #+#    #+#             */
/*   Updated: 2026/08/01 16:44:11 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmlx.h"

static int	close_window(void *param)
{
	mlx_loop_end(((t_mlx *)param)->instance);
	return (0);
}

static int	save_ppm(t_mlx *mlx, char *filename)
{
	unsigned char	*out;
    unsigned char	*src;
	FILE			*f;
    int 			out_i;
    int 			size;

	size = W_WIDTH * W_HEIGHT * 3;
	out = malloc(size);
	if (!out)
		return(1);
	src = (unsigned char *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->end);
	out_i = 0;
    for (int y = 0; y < W_HEIGHT; y++)
    {
        for (int x = 0; x < W_WIDTH; x++)
        {
            unsigned char *pixel = src + (y * mlx->len) + (x * (mlx->bpp / 8));
            out[out_i++] = pixel[2];
            out[out_i++] = pixel[1];
            out[out_i++] = pixel[0];
        }
    }
	f = fopen(filename, "wb");
    fprintf(f, "P6\n%d %d\n255\n", W_WIDTH, W_HEIGHT);
    fwrite(out, 1, size, f);
    fclose(f);
    free(out);
	return (0);
}

static int	on_keypress(int keycode, void *param)
{
	if (keycode == 65307)
		return (close_window(param));
	if (keycode == 115)
		return (save_ppm(param, "render.ppm"));
	return (0);
}

static void	set_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1L << 0, &on_keypress, mlx);
	mlx_hook(mlx->win, 17, 0, &close_window, mlx);
}

int	del_mlx(t_mlx *mlx, int exit_no)
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
	return (exit_no);
}

int	window_run(t_mlx *mlx, uint32_t *image, char *filename)
{
	char		*w;

	w = ft_strjoin("miniRT - ", filename);
	mlx->win = mlx_new_window(mlx->instance, W_WIDTH, W_HEIGHT, (char *) w);
	free(w);
	if (!mlx->win)
		return (del_mlx(mlx, 1));
	mlx->img = mlx_new_image(mlx->instance, W_WIDTH, W_HEIGHT);
	if (!mlx->img)
		return (del_mlx(mlx, 1));
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->end);
	if (mlx->bpp != 32 || mlx->len != W_WIDTH * 4)
		return (del_mlx(mlx, 1));
	ft_memcpy(mlx->addr, image, W_WIDTH * W_HEIGHT * sizeof(uint32_t));
	mlx_put_image_to_window(mlx->instance, mlx->win, mlx->img, 0, 0);
	set_hooks(mlx);
	mlx_loop(mlx->instance);
	return (0);
}
