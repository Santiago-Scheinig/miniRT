/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/22 18:12:48 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"

int	rtapp_init(int argc, char **argv, t_rtapp *app)
{
	t_list	*aux;

	if (argc != 2)
		return (RTERR_FAILURE);//log("[ms][pid]: Invalid number of arguments\nOnly one .rt file can be proccessed at the same time\n");
	aux = parser(argv);//log("[ms][pid]: Invalid '%c' character on line '%i' in *.rt file\n") || errlog("[ms][pid]: Invalid parameters for '%s' objects on line '%i' in *.rt file\nPlease verify the correct format:\n['%s' format]: xxxxx";
	if (!aux)
		return (RTERR_FAILURE);
	//log("[ms][pid]: *.rt file validated.")
	if (init_log(app))
		return (RTERR_SUCCESS);//log("[ms][pid]: Unable to initialize log and errlog files\n");
	//log("[ms][pid]: log.txt, errlog.txt files created.");
	//log("[ms][pid]: STDOUT_FILENO, STDERR_FILENO fds redirected to log.txt, errlog.txt files respectibly.");
	if (init_objlst(aux, app))
		return (RTERR_FAILURE);//errlog("[ms][pid]: Unable to initialize the necesary memory to run the application\n";
	//log("[ms][pid]: objects list initializated.");
	//log("[ms][pid]: rtapp_init succesfull.");
	return (RTERR_SUCCESS);
}

/* rtapp_render()

rtapp_run() */

int rtapp_kill(t_rtapp *app)
{
	return (RTERR_SUCCESS);
}