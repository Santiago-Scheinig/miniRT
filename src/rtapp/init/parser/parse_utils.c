/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:13:33 by sscheini          #+#    #+#             */
/*   Updated: 2026/05/19 19:55:56 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp_parser.h"

t_dlim	build_limit(double min, double max)
{
	t_dlim	new;

	new.min = min;
	new.max = max;
	return (new);
}

/**
 * Validates that a string represents a double within the given limits.
 * @param str The full double string to validate and range-check.
 * @param split The string split by '.', used to check digit validity.
 * @param limits The T_DLIM containing the accepted min and max range.
 * @return RT_SUCCESS if the string is a valid double within limits,
 * RT_FAILURE if any character is invalid or the value is out of range.
 * @note Only digits and a leading '-' sign are accepted as valid chars.
 */
static int	double_check(char *str, char **split, t_dlim limits)
{
	double	aux;
	int		i;

	if (!split || !split[0])
		return (RT_FAILURE);
	i = 0;
	if (split[0][0] == '-')
		i = 1;
	while (split[0][i])
	{
		if (!ft_isdigit(split[0][i]))
			return (RT_FAILURE);
		i++;
	}
	if (split[1])
	{
		if (ft_strlen(split[1]) > 1)
			return (RT_FAILURE);
		if (!ft_isdigit(split[1][0]))
			return (RT_FAILURE);
	}
	aux = ft_atod(str);
	if (aux > limits.max || aux < limits.min)
		return (RT_FAILURE);
	return (RT_SUCCESS);
}

int	parse_double(char *sp, char *str, int i, t_dlim limits)
{
	const char	*err = "[line: %i][%s] parser failed: %s";
	char		**split;
	int			ans;

	ans = RT_SUCCESS;
	if (!str)
		return (RT_FAILURE);
	split = ft_split(str, '.');
	if (!split)
		return (rtlog(RT_ERRLOG, 0, err, i, sp, strerror(errno)));
	if (ft_arglen(split) > 2)
		ans = RT_FAILURE;
	if (double_check(str, split, limits))
		ans = RT_FAILURE;
	ft_split_free(split);
	return (ans);
}

/**
 * Validates that a comma-split vector has exactly three valid components.
 * @param sp The element specifier string, used for error logging.
 * @param split The array of strings from splitting the vector by ','.
 * @param line The line number in the scene file, used for error logging.
 * @param limits The T_DLIM containing the accepted range per component.
 * @return RT_SUCCESS if all three components are valid doubles within
 * limits and no excess components exist, RT_FAILURE otherwise.
 */
static int	vector_check(char *sp, char **split, int line, t_dlim limits)
{
	int			ans;

	ans = RT_SUCCESS;
	if (parse_double(sp, split[0], line, limits))
		ans = RT_FAILURE;
	else if (parse_double(sp, split[1], line, limits))
		ans = RT_FAILURE;
	else if (parse_double(sp, split[2], line, limits))
		ans = RT_FAILURE;
	else if (split[3])
		ans = RT_FAILURE;
	return (ans);
}

int	parse_vector(char *sp, char *str, int i, t_dlim limits)
{
	const char	*errmsg = "[line: %i][%s] parser failed: %s";
	char		**split;

	split = ft_split(str, ',');
	if (!split)
		return (rtlog(RT_ERRLOG, 0, errmsg, i, sp, strerror(errno)));
	if (vector_check(sp, split, i, limits))
	{
		ft_split_free(split);
		return (RT_FAILURE);
	}
	ft_split_free(split);
	return (RT_SUCCESS);
}
