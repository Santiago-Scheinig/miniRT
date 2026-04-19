/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:11:04 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 20:41:21 by sscheini         ###   ########.fr       */
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
	t_rtapp	app;

	memset(&app, 0, sizeof(t_rtapp));
	if (rtapp_init(argc, argv, &app))
		rtapp_kill(&app, RT_FAILURE);
/* 	if (!rtapp_render(app))
		return (rtapp_kill(&app, RT_FAILURE));
	if (!rtapp_run(app.img))
		return (rtapp_kill(&app, RT_FAILURE)); */
	rtapp_kill(&app, RT_SUCCESS);
	return (RT_SUCCESS);
}
