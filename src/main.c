/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:11:04 by sscheini          #+#    #+#             */
/*   Updated: 2026/06/09 18:11:48 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"

/**
 * Entry point of the miniRT application.
 * @param argc The number of command line arguments.
 * @param argv The array of command line argument strings, where argv[1]
 * is the path to the scene file.
 * @return RT_SUCCESS after the application exits cleanly.
 * @note The app is zero-initialized with memset before being passed to
 * rtapp_init. Both failure and success paths go through rtapp_kill to
 * ensure all resources are freed and file descriptors are restored.
 * @note BONUS: rtapp_render and rtapp_run are stubbed out pending full
 * rendering and window management implementation.
 */
int	main(int argc, char **argv)
{
	const char	*err = "main: application initialization failed: %s";
	t_rtapp		app;

	ft_memset(&app, 0, sizeof(t_rtapp));
	app.img = ft_calloc(W_HEIGHT * W_WIDTH, sizeof(uint32_t));
	if (!app.img)
		return (rtlog(RT_ERRLOG, 0, err, strerror(errno)), RT_FAILURE);
	app.mlx.instance = mlx_init();
	if (!app.mlx.instance)
	{
		free(app.img);
		return (del_mlx(&app.mlx, 1));
	}
	if (rtapp_init(argc, argv, &app))
		return (rtapp_kill(&app, RT_FAILURE));
	if (rtapp_render(&app))
		return (rtapp_kill(&app, RT_FAILURE));
	if (window_run(&app.mlx, app.img, argv[1]))
		return (rtapp_kill(&app, RT_FAILURE));
	rtapp_kill(&app, RT_SUCCESS);
	return (RT_SUCCESS);
}
