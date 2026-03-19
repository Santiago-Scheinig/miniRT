/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 17:08:47 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/19 18:12:54 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * mlx_program_tester.c is a file wit a build-int main that uses the the minilibx,
 * allowing to test the improvemts build in miniRT without the need to run the 
 * whole miniRT program.
 * 
 * Its main purpuse its to be copied into different branches and modify it as
 * needed to test the different improvements and features of miniRT.
 * 
 * This file should not be modified in the main branch, but only in the branches 
 * where the improvements are being developed.
 * 
 * Can it be added on the .gitignore after being uploaded to the main branch?
 * That way we left it in the main branch intact, and can modify it freely in the
 * different branches without worrying about merge conflicts.
 * 
 * To run the code [until applied on a special makefile as test rule]:
 * 
 * gcc mlx_program_tester.c -I ../minilibx-linux  -L ../minilibx-linux -lmlx -lXext -lX11 -lm -o program
 * 
 * A good modular makefile can help with testing of functions.
 * 
 */

# include "../minilibx-linux/mlx.h"

int	main(void)
{
	void	*mlx;
	void	*win;

	
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "MiniRT - Minilibx Tester");
	mlx_loop(mlx);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	return (0);
}