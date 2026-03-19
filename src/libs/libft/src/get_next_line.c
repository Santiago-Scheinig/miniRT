/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:11:45 by root              #+#    #+#             */
/*   Updated: 2025/06/02 10:44:55 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Failsafe specific to get_next_line in case of error.
 * - Frees every position of text, returning NULL to indicate an error
 *	 ocurred.
 */
static	void	*ft_forcend(char **txt, char *ft_error)
{
	int		i;

	i = -1;
	while (txt[++i])
	{
		free(txt[i]);
		txt[i] = NULL;
	}
	perror(ft_error);
	return (NULL);
}

/**
 * Allocates a new char * with BUFFER SIZE ready to read into.
 * - Notice that if the previous char * had any information, it will create
 *   a new char * with str_len + BUFFER SIZE, and copy the information.
 */
static	char	*ft_new_text(char *str)
{
	char	*aux;
	int		str_len;

	if (!str)
	{
		str = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!str)
			return (NULL);
		return (str);
	}
	aux = str;
	str_len = ft_strlend(str, 0);
	str = ft_calloc((str_len + BUFFER_SIZE + 1), sizeof(char));
	if (!str)
	{
		free(aux);
		return (NULL);
	}
	ft_strlcpy(str, aux, str_len + 1);
	free(aux);
	return (str);
}

/**
 * Reads the file descriptor into txt until it reads a full a line or EOF.
 */
static	char	*ft_read_text(char *txt, int fd)
{
	int	line;
	int	r_ans;

	line = 0;
	if (txt)
		line = ft_strlend(txt, '\n');
	while (!line)
	{
		txt = ft_new_text(txt);
		if (!txt)
			return (NULL);
		r_ans = read(fd, &txt[ft_strlend(txt, 0)], BUFFER_SIZE);
		if (r_ans < 0)
		{
			free(txt);
			return (NULL);
		}
		if (!r_ans || txt[0] == '\n')
			return (txt);
		line = ft_strlend(txt, '\n');
	}
	return (txt);
}

/**
 * Returns a full line found on txt.
 * - Notice that the function will cut the line from the static variable.
 */
static	char	*ft_line_text(char **txt)
{
	char	*line;
	char	*aux;
	int		line_len;
	int		end;

	line_len = ft_strlend((*txt), '\n') + 1;
	if (line_len == 1)
	{
		if ((*txt)[0] == '\n')
			line_len = 1;
		else
			line_len = ft_strlend((*txt), 0);
	}
	line = ft_calloc((line_len + 1), sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, (*txt), line_len + 1);
	aux = (*txt);
	end = ft_strlen(&(*txt)[line_len]);
	ft_rewrite(txt, line_len, end);
	if (end)
		ft_strlcpy((*txt), &aux[line_len], end + 1);
	free(aux);
	return (line);
}

/**
 * Returns a char * with the next line on the file descriptor given.
 */
char	*get_next_line(int fd)
{
	static char	*txt[1000];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	txt[fd] = ft_read_text(txt[fd], fd);
	if (!txt[fd])
		return (ft_forcend(txt, "Ft_read_text"));
	if (!txt[fd][0])
	{
		free(txt[fd]);
		txt[fd] = NULL;
		line = NULL;
	}
	else
		line = ft_line_text(&txt[fd]);
	if (!line && txt[fd])
	{
		errno = EIO;
		return (ft_forcend(txt, "Ft_line_text"));
	}
	return (line);
}
