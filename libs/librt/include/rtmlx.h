/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtmlx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:25:00 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/19 21:18:48 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTMLX_H
# define RTMLX_H

# ifndef SCREEM_WIDTH
# 	define SCREEN_WIDTH 1920
# endif
# ifndef SCREEM_HEIGHT
#  define SCREEN_HEIGHT 1080
# endif

/**
 * @file rtmlx.h  
 * @brief MiniLibX abstraction layer for librt window and image management.
 * @todo Declare mlx_set_hooks() mlx_replace_image() mlx_window_run()
 * mlx_window_kill() as tools for future apps to use at window execution.
 * @note Currently holds only screen dimension constants. To be extended
 * with window lifecycle and pixel buffer functions as the render
 * pipeline is implemented.
 */

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif