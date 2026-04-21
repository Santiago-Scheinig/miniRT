/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtmlx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:25:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/21 19:05:06 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTMLX_H
# define RTMLX_H
# include "mlx.h"
# include "libft.h"
# include <stdint.h>
# ifndef SCREEN_WIDTH
# 	define SCREEN_WIDTH 1920
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 1080
# endif

typedef struct s_mlx
{
    void    *instance;     // connection handle
    void    *win;     // window handle
    void    *img;     // image handle
    char    *addr;    // pixel buffer address
    int     bpp;      // bits per pixel
    int     line_len; // bytes per row
    int     endian;   // byte order
}   t_mlx;

int	window_run(uint32_t *image);

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif