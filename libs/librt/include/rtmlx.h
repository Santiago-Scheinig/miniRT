/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtmlx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:25:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/06/09 18:07:20 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTMLX_H
# define RTMLX_H
# include "mlx.h"
# include "libft.h"
# include <stdint.h>
# ifndef W_WIDTH
#  define W_WIDTH 1920
# endif
# ifndef W_HEIGHT
#  define W_HEIGHT 1080
# endif

typedef struct s_mlx
{
	void	*instance;	// connection handle
	void	*win;		// window handle
	void	*img;		// image handle
	char	*addr;		// pixel buffer address
	int		bpp;		// bits per pixel
	int		len;		// bytes per row
	int		end;		// byte order
}	t_mlx;

int	window_run(t_mlx *mlx, uint32_t *image, char *filename);

int	del_mlx(t_mlx *mlx, int exit_no);

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif