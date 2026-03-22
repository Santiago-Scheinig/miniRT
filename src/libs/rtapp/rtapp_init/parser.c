/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:11:27 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/22 19:49:31 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"

static int	validate_lines(t_list **lines)
{
	t_list	*aux;
	
	aux = (*lines);
	while (aux)
	{
		//log("[ms][pid]: Invalid '%c' character on line '%i' in *.rt file\n")
		//|| errlog("[ms][pid]: Invalid parameters for '%s' objects on line '%i' in *.rt file\n
		//Please verify the correct format:\n['%s' format]: xxxxx";
		aux = aux->next;
	}
	return (RT_SUCCESS);
}

static int	validate_filename(char *file)
{
	char	*aux;
	
	aux = ft_strrchr(file, '.');
	if (!aux)
	{
		rtlog(RT_ERRLOG, 0, "Invalid file '%s'. Use a valid .rt file", file);
		return (RT_FAILURE);
	}
	aux++;
	if (ft_strncmp(aux, "rt", 2))
	{
		rtlog(RT_ERRLOG, 0, "Invalid file '%s'. Use a valid .rt file", file);
		return (RT_FAILURE);
	}
	return (RT_SUCCESS);
}

t_list	*parser(char *file)
{
	t_list	*lines;
	int		fd;

	lines = NULL;
	if (validate_filename(file))
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
	if (validate_lines(&lines))
	{
		ft_lstclear(&lines, free);	
		return (NULL);
	}
	rtlog(RT_LOG, 0, "'%s' file contents validated.", file);
	return (lines);
}
