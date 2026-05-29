/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:13:33 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/24 20:15:46 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

static int	parse_flag(char *sp, char *str, int i)
{
	const char	*err = "[line: %i][%s]: \'%s\' %s";
	const char	*msg = "is an invalid flag.";

	if (str[0] == '-')
	{
		if (ft_strncmp("-ch", str, 4))
			return (rtlog(RT_ERRLOG, 0, err, i, sp, str, msg));
		return (RT_SUCCESS);
	}
	return (RT_FAILURE);
}

static int	check_phong(char *sp, char **split, int i)
{
	const char	*err = "[line: %i][%s]: \'%s\' %s";
	const char	*msg_vec = "is an invalid specular intesity vector [0.0-1.0].";
	const char	*msg_exp = "is outside the specular exponent [1-256].";

	if (parse_vector(sp, &split[0][2], i, build_limit(0.0, 1.0)))
		return (rtlog(RT_ERRLOG, 0, err, i, sp, split[0], msg_vec));
	if (parse_double(sp, split[1], i, build_limit(1, 256)))
		return (rtlog(RT_ERRLOG, 0, err, i, sp, split[1], msg_exp));
	return (RT_SUCCESS);
}

static int	parse_phong(char *sp, char *str, int i)
{
	const char	*err = "[line: %i][%s]: \'%s\' %s";
	const char	*msg_inv = "invalid format: [P=R,G,B^e].";
	char		**split;

	if (str[0] == 'P' && str[1] == '=')
	{
		split = ft_split(str, '^');
		if (!split)
			return (rtlog(RT_ERRLOG, 0, "[line: %i][%s]:", i, strerror(errno)));
		if (ft_arglen(split) != 2)
		{
			ft_split_free(split);
			return (rtlog(RT_ERRLOG, 0, err, i, sp, str, msg_inv));
		}
		if (check_phong(sp, split, i))
		{
			ft_split_free(split);
			return (RT_FAILURE);
		}
		return (RT_SUCCESS);
	}
	return (RT_FAILURE);
}

static int	parse_texture(char *sp, char *str, int i, char *extention)
{
	const char	*err = "[line: %i][%s]: \'%s\' %s";
	const char	*msg = "uses an invalid extention.";

	if (ft_strnstr(str, extention, ft_strlen(str)))
		return (RT_SUCCESS);
	return (rtlog(RT_ERRLOG, 0, err, i, sp, str, msg));
}

int	parse_add_att(char **arr, int index, int line)
{
	const char	*err = "[line: %i][%s] parser failed: \'%s\' %s.";
	const char	*msg = "is an invalid additional attribute";
	int			arrlen;

	arrlen = ft_arglen(arr);
	while (index < arrlen)
	{
		if (parse_flag(arr[0], arr[index], line)
			&& parse_phong(arr[0], arr[index], line)
			&& parse_texture(arr[0], arr[index], line, ".xpm"))
			return (rtlog(RT_ERRLOG, 0, err, line, arr[0], arr[index], msg));
		index++;
	}
	return (RT_SUCCESS);
}
