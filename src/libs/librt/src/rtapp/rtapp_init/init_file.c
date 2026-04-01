/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:11:27 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 17:37:07 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"

static int	file_validate(char *file)
{
	char	*aux;
	
	aux = ft_strrchr(file, '.');
	if (!aux)
	{
		rtlog(RT_ERRLOG, 0, "Invalid file '%s': use a valid .rt file", file);
		return (RT_FAILURE);
	}
	aux++;
	if (ft_strncmp(aux, "rt", 2))
	{
		rtlog(RT_ERRLOG, 0, "Invalid file '%s': use a valid .rt file", file);
		return (RT_FAILURE);
	}
	return (RT_SUCCESS);
}

t_list	*init_file(char *file)
{
	t_list	*lines;
	int		fd;

	lines = NULL;
	if (file_validate(file))
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		rtlog(RT_ERRLOG, 0, "Failed to open '%s': %s", file, strerror(errno));
		return (NULL);
	}
	if (ft_read_file(&lines, fd) == -1)
	{
		rtlog(RT_ERRLOG, 0, "Failed to read '%s': %s", file, strerror(errno));
		return (NULL);
	}
	close(fd);
	return (lines);
}
