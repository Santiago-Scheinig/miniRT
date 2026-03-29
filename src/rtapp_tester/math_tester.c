/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tester.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:54:48 by aramos-r          #+#    #+#             */
/*   Updated: 2026/03/29 17:11:38 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"
#include <stdio.h>

static int    test_vector_mult_scalar(void)
{
    t_vector v = vector_new(1.0, 2.0, 3.0);
    t_vector result = vector_mult_scalar(v, 2.0);
    if (result.x == 2.0 && result.y == 4.0 && result.z == 6.0)
        return (0);
    else
        return (1);
}

static int    test_vector_div_scalar(void)
{
    t_vector v = vector_new(2.0, 4.0, 6.0);
    t_vector result = vector_div_scalar(v, 2.0);
    if (!(result.x == 1.0 && result.y == 2.0 && result.z == 3.0))
        return (1);
    result = vector_div_scalar(v, 0.0);
    if (!(result.x == 0.0 && result.y == 0.0 && result.z == 0.0))
        return (1);
    return (0);
}

static int    test_vector_new(void)
{
    t_vector v = vector_new(1.0, 2.0, 3.0);
    if (v.x == 1.0 && v.y == 2.0 && v.z == 3.0)
        return (0);
    else
        return (1);
}

static void    test_function( int (*f)(void), char* name )
{
    if (f() == 0)
        printf("%s: OK\n", name);
    else
        printf("%s: FAIL\n", name);
}

int main(void)
{
    int (*tests[])(void) = {
        test_vector_new,
        test_vector_mult_scalar,
        test_vector_div_scalar,
    };
    char* test_names[] = {
        "test_vector_new",
        "test_vector_mult_scalar",
        "test_vector_div_scalar",
    };
    for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
        test_function(tests[i], test_names[i]);
    return (0);
}
