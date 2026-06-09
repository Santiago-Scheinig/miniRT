/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:11:27 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/23 20:22:33 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"
#include "rtapp_parser.h"

int	init_file_contents(t_list *lines, char *file, t_rtapp *app)
{
	const char	*err = "compilation of %s file failed: %s";
	t_list		*head;
	int			i;

	rtlog(RT_LOG, 0, "< Compiling '%s' file >", file);
	i = 1;
	app->ambient.ratio = -1;
	head = lines;
	while (lines)
	{
		if (parse_line(lines, i, app))
		{
			ft_lstclear(&head, free);
			return (RT_FAILURE);
		}
		lines = lines->next;
		i++;
	}
	ft_lstclear(&head, free);
	if (app->ambient.ratio == -1)
		return (rtlog(RT_ERRLOG, 0, err, file, "no ambient light defined."));
	if (!app->camera.get_pixel_ray)
		return (rtlog(RT_ERRLOG, 0, err, file, "no camera defined."));
	return (rtlog(RT_LOG, 0, "< Compilation successful >", file));
}

/**
 * Validates that a file path has a .rt extension.
 * @param file The file path string to validate.
 * @return RT_SUCCESS if the file has a .rt extension, RT_FAILURE if the
 * extension is missing or does not match.
 */
static int	file_validate(char *file)
{
	const char	*err = "failed to open '%s': %s";
	char		*aux;

	aux = ft_strrchr(file, '.');
	if (!aux)
		return (rtlog(RT_ERRLOG, 0, err, file, "invalid .rt file"));
	aux++;
	if (ft_strncmp(aux, "rt", 3))
		return (rtlog(RT_ERRLOG, 0, err, file, "invalid .rt file"));
	return (RT_SUCCESS);
}

static t_list	*read_and_close(int fd, char *file)
{
	const char		*err = "failed to open '%s': %s";
	t_list			*lines;

	lines = NULL;
	if (ft_read_file(&lines, fd) == -1)
	{
		close(fd);
		rtlog(RT_ERRLOG, 0, err, file, strerror(errno));
		return (NULL);
	}
	close(fd);
	if (!lines)
		rtlog(RT_ERRLOG, 0, err, file, "empty file.");
	return (lines);
}

t_list	*init_file(char *file)
{
	const char	*err = "failed to open '%s': %s";
	int			fd;

	if (file_validate(file))
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		rtlog(RT_ERRLOG, 0, err, file, strerror(errno));
		return (NULL);
	}
	return (read_and_close(fd, file));
}
