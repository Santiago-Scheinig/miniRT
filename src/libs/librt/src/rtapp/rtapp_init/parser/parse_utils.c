/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:13:33 by sscheini          #+#    #+#             */
/*   Updated: 2026/03/25 21:12:59 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_init.h"

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
		aux = ft_atof(split[i]);
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

int parse_vector(char *sp, char *str, int i, t_flim limits)
{
	const char	*errmsg = "Parser error for %s in line %i: %s";
	char		**split;
	int			ans;
	
	ans = RT_SUCCESS;
	split = ft_split(str, ',');
	if (!split)
	{
		rtlog(RT_ERRLOG, 0, errmsg, sp, i, strerror(errno));	
		return (RT_FAILURE);
	}
	if (parse_float(sp, split[0], i, limits))
		ans = RT_FAILURE;
	else if (parse_float(sp, split[1], i, limits))
		ans = RT_FAILURE;
	else if (parse_float(sp, split[2], i, limits))
		ans = RT_FAILURE;
	else if (split[3])
	{
		rtlog(RT_ERRLOG, 0, errmsg, sp, i, "vector must be 3D.");
		ans = RT_FAILURE;
	}
	ft_split_free(split);
	return (ans);
}

int	parse_color(char *sp, char *str, int i)
{
	const char	*errmsg = "Parser error for %s in line %i: %s";

	//Maybe this must return an int8_u, but we can change that later on;
	rtlog(RT_ERRLOG, 0, errmsg, sp, i, "invalid color.");
}

t_object	*new_obj(char **split, void *(*constructor)(char **))
{
	t_object		*obj;
	const char		*errmsg = "Failed to initialize %s: %s";

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		rtlog(RT_ERRLOG, 0, errmsg, split[0], strerror(errno));
		return (NULL);
	}
	obj->data = constructor(split);
	if (!obj->data)
	{
		rtlog(RT_ERRLOG, 0, errmsg, split[0], strerror(errno));
		free(obj);
		return (NULL);
	}
	return (obj);
}
