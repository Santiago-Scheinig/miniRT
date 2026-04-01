/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:13:33 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 17:48:19 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

static int	float_check(char *sp, char **split, int line, t_flim limits)
{
	const char	*errmsg = "Parser error for %s in line %i: %s";
	float		aux;
	int	i;
	int	j;

	i = -1;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
		{
			if (!ft_isdigit(split[i][j]))
			{
				rtlog(RT_ERRLOG, 0, errmsg, sp, line, "invalid float.");
				return (RT_FAILURE);
			}
		}
		aux = atof(split[i]);//need our own
		if (aux > limits.max || aux < limits.min)
		{
			rtlog(RT_ERRLOG, 0, errmsg, sp, line, "float outside limits.");
			return (RT_FAILURE);
		}
	}
	return (RT_SUCCESS);
}

int	parse_float(char *sp, char *str, int i, t_flim limits)
{
	const char	*errmsg = "Parser error for %s in line %i: %s";
	char		**split;
	int			ans;

	ans = RT_SUCCESS;
	if (!str)
	{
		rtlog(RT_ERRLOG, 0, errmsg, sp, i, "missing float point.");
		return (RT_FAILURE);
	}
	split = ft_split(str, '.');
	if (!split)
	{
		rtlog(RT_ERRLOG, 0, "Failed initialize %s: %s", sp, strerror(errno));
		return (RT_FAILURE);
	}
	if (ft_arglen(split) > 2)
	{
		rtlog(RT_ERRLOG, 0, errmsg, sp, i, "invalid float.");
		ans = RT_FAILURE;
	}
	if (float_check(sp, split, i, limits))
		ans = RT_FAILURE;
	ft_split_free(split);
	return (ans);
}

static int	vector_check(char *sp, char **split, int line, t_flim limits)
{
	const char	*errmsg = "Parser error for %s in line %i: %s";
	t_vector	v;
	int			ans;

	ans = RT_SUCCESS;
	if (parse_float(sp, split[0], line, limits))
		ans = RT_FAILURE;
	else if (parse_float(sp, split[1], line, limits))
		ans = RT_FAILURE;
	else if (parse_float(sp, split[2], line, limits))
		ans = RT_FAILURE;
	else if (split[3])
	{
		rtlog(RT_ERRLOG, 0, errmsg, sp, line, "invalid 3D vector.");
		ans = RT_FAILURE;
	}
	v.x = atof(split[0]);//Need to change to ours
	v.y = atof(split[1]);//Need to change to ours
	v.z = atof(split[2]);//Need to change to ours
	if (!v.x && !v.y && !v.z)
		ans = RT_FAILURE;
	return (ans);
}

int parse_vector(char *sp, char *str, int i, t_flim limits)
{
	const char	*errmsg = "Parser error for %s in line %i: %s";
	char		**split;
	
	split = ft_split(str, ',');
	if (!split)
	{
		rtlog(RT_ERRLOG, 0, errmsg, sp, i, strerror(errno));	
		return (RT_FAILURE);
	}
	if (vector_check(sp, split, i, limits))
	{
		ft_split_free(split);
		return (RT_FAILURE);
	}
	ft_split_free(split);
	return (RT_SUCCESS);
}

int	parse_color(char *sp, char *str, int i)
{
	const char	*errmsg = "Parser error for %s in line %i: %s";

	(void)str;
	(void)sp;
	(void)i;
	rtlog(RT_ERRLOG, 0, errmsg, sp, i, "feat unfinished.");
	return (0);
}
