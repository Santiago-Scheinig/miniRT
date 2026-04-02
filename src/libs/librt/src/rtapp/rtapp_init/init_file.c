/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:11:27 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 19:49:20 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"

static int	file_validate(char *file)
{
	const char	*errmsg = "Invalid file '%s': %s";
	char	*aux;
	
	aux = ft_strrchr(file, '.');
	if (!aux)
		return (rtlog(RT_ERRLOG, 0, errmsg, file, "invalid .rt file"));
	aux++;
	if (ft_strncmp(aux, "rt", 2))
		return (rtlog(RT_ERRLOG, 0, errmsg, file, "invalid .rt file"));
	return (RT_SUCCESS);
}

t_list	*init_file(char *file)
{
	const char	*errmsg = "Failed to open '%s': %s";
	t_list	*lines;
	int		fd;

	lines = NULL;
	if (file_validate(file))
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		rtlog(RT_ERRLOG, 0, errmsg, file, strerror(errno));
		return (NULL);
	}
	if (ft_read_file(&lines, fd) == -1)
	{
		rtlog(RT_ERRLOG, 0, errmsg, file, strerror(errno));
		return (NULL);
	}
	if (!lines)
	{
		rtlog(RT_ERRLOG, 0, errmsg, file, "empty file.");
		return (NULL);
	}
	close(fd);
	return (lines);
}
