/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_scalar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 15:00:21 by aramos-r          #+#    #+#             */
/*   Updated: 2026/03/29 17:03:52 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"

t_vector	vector_mult_scalar(t_vector v, double scalar)
{
    t_vector	result;

    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    return (result);
}

t_vector	vector_div_scalar(t_vector v, double scalar)
{
    t_vector	result;

    if (scalar == 0.0f)
    {
        result.x = 0.0f;
        result.y = 0.0f;
        result.z = 0.0f;
    }
    else
    {
        result.x = v.x / scalar;
        result.y = v.y / scalar;
        result.z = v.z / scalar;
    }
    return (result);
}
