/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:38:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/06/09 17:38:07 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_H
# define RTAPP_H

# include "libft.h"
# include "rtelm.h"
# include "rterr.h"
# include "rtmlx.h"
# include "rtmth.h"
# include "rtapp_debug.h"
# include "rtapp_bonus_types.h"

# ifndef DEV
#  define DEV 0
# endif

/*--------------------------------------------------------------------------*/
/*--------------------------------STRUCTURES--------------------------------*/
/*--------------------------------------------------------------------------*/

typedef struct s_tile
{
	int			x_start;
	int			y_start;
	int			x_end;
	int			y_end;
	uint32_t	*(*get_pixel_ptr)(uint32_t *img, int x, int y);
}	t_tile;

typedef struct s_tile_queue
{
	int	current_x;
	int	current_y;
}	t_tile_queue;

typedef struct s_rtapp
{
	uint32_t		*img;
	t_list			*objects;
	t_list			*lights;
	t_mlx			mlx;
	t_elem_camera	camera;
	t_elem_light_a	ambient;
	t_tile_queue	tile_queue;
	t_rtapp_bonus	bonus;
}	t_rtapp;

/*--------------------------------------------------------------------------*/
/*--------------------------------APP_STEPS---------------------------------*/
/*--------------------------------------------------------------------------*/

int	rtapp_init(int argc, char **argv, t_rtapp *app);

int	rtapp_kill(t_rtapp *app, t_rterr errcode);

int	rtapp_render(t_rtapp *app);

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif