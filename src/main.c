/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:11:04 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/19 18:46:04 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"

int	main(int argc, char **argv)
{
	t_rtapp	app;

	app = rtapp_init(argv);
	if (!app)
		return (appfree(app));
	if (!rtapp_render(app))
		return (appfree(app));
	if (!rtapp_run(app.img))
		return (appfree(app));
	if (!rtapp_kill(app))
		return (appfree(app));
	return (0);
}
