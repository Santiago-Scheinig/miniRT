/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:11:04 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/27 16:51:31 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"

int	main(int argc, char **argv)
{
	t_rtapp	app;

	memset(&app, 0, sizeof(t_rtapp));
	if (rtapp_init(argc, argv, &app))
		rtapp_kill(&app, RT_FAILURE);
/* 	if (!rtapp_render(app))
		return (appfree(app));
	if (!rtapp_run(app.img))
		return (appfree(app)); */
	rtapp_kill(&app, RT_SUCCESS);
	return (RT_SUCCESS);
}
