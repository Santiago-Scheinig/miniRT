/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:13:33 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/06 17:01:30 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

static int	float_check(char *str, char **split, t_flim limits)
{
	float	aux;
	int		i;
	int		j;

	i = -1;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
			if (split[i][0] != '-' && !ft_isdigit(split[i][j]))
					return (RT_FAILURE);
	}
	aux = atof(str);//need our own
	if (aux > limits.max || aux < limits.min)
		return (RT_FAILURE);
	return (RT_SUCCESS);
}

int	parse_double(char *sp, char *str, int i, t_flim limits)
{
	const char	*errmsg = "Failed to initialize %s in line %i: %s";
	char		**split;
	int			ans;

	ans = RT_SUCCESS;
	if (!str)
		return (RT_FAILURE);
	split = ft_split(str, '.');
	if (!split)
		return (rtlog(RT_ERRLOG, 0, errmsg, sp, i, strerror(errno)));
	if (ft_arglen(split) > 2)
		ans = RT_FAILURE;
	if (float_check(str, split, limits))
		ans = RT_FAILURE;
	ft_split_free(split);
	return (ans);
}

static int	vector_check(char *sp, char **split, int line, t_flim limits)
{
	int			ans;

	ans = RT_SUCCESS;
	if (parse_double(sp, split[0], line, limits))
	{
		ans = RT_FAILURE;
	}
	else if (parse_double(sp, split[1], line, limits))
		ans = RT_FAILURE;
	else if (parse_double(sp, split[2], line, limits))
		ans = RT_FAILURE;
	else if (split[3])
		ans = RT_FAILURE;
	return (ans);
}

int parse_vector(char *sp, char *str, int i, t_flim limits)
{
	const char	*errmsg = "Failed to initialize %s in line %i: %s";
	char		**split;
	
	split = ft_split(str, ',');
	if (!split)
		return (rtlog(RT_ERRLOG, 0, errmsg, sp, i, strerror(errno)));
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
	const char	*errmsg = "Failed to initialize %s in line %i: %s";
	char		**split;
	t_flim		limits;
	int			ans;
	
	limits.min = 0;
	limits.max = 255;
	ans = RT_SUCCESS;
	split = ft_split(str, ',');
	if (!split)
	{
		rtlog(RT_ERRLOG, 0, errmsg, sp, i, strerror(errno));
		ans = RT_FAILURE;
	}
	if (parse_double(sp, split[0], i, limits))
		ans = RT_FAILURE;
	else if (parse_double(sp, split[1], i, limits))
		ans = RT_FAILURE;
	else if (parse_double(sp, split[2], i, limits))
		ans = RT_FAILURE;
	else if (split[3])
		ans = RT_FAILURE;
	ft_split_free(split);
	return (RT_SUCCESS);
}
