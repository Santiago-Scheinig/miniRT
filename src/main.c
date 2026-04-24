/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:11:04 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/24 12:18:24 by aramos-r         ###   ########.fr       */
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
	struct timespec	start, end, total_start, total_end;
	double			elapsed;

	clock_gettime(CLOCK_MONOTONIC, &total_start);

	ft_memset(&app, 0, sizeof(t_rtapp));
	app.img = ft_calloc(SCREEN_HEIGHT * SCREEN_WIDTH, sizeof(uint32_t));
	if (!app.img)
		return (rtlog(RT_ERRLOG, 0, err, strerror(errno)), RT_FAILURE);

	// Init
	printf("Starting Rtapp init...\n");
	clock_gettime(CLOCK_MONOTONIC, &start);

	if (rtapp_init(argc, argv, &app))
		rtapp_kill(&app, RT_FAILURE);

	clock_gettime(CLOCK_MONOTONIC, &end);
	elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
	printf("Rtapp init finished in %.3f seconds\n\n", elapsed);
	
	// Render
	printf("Starting render...\n");
	clock_gettime(CLOCK_MONOTONIC, &start);

	if (rtapp_render(&app))
		return (rtapp_kill(&app, RT_FAILURE));

	clock_gettime(CLOCK_MONOTONIC, &end);
	elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
	printf("Render finished in %.3f seconds\n\n", elapsed);

	clock_gettime(CLOCK_MONOTONIC, &total_end);
	elapsed = (total_end.tv_sec - total_start.tv_sec) + (total_end.tv_nsec - total_start.tv_nsec) / 1e9;
	printf("Total execution time: %.3f seconds\n\n-----------------------\n\n", elapsed);

	// Run window
	if (window_run(app.img, argv[1]))
		return (rtapp_kill(&app, RT_FAILURE));
	rtapp_kill(&app, RT_SUCCESS);
	return (RT_SUCCESS);
}
