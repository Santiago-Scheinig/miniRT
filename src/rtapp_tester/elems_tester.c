/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:58:29 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/02 14:48:05 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtelm.h"
#include <stdio.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static void	print_header(void)
{
	printf("\e[1;34m====================\n");
	printf("   ELEMS TESTER\n");
	printf("====================\e[0m\n");
}

static void	test_function( int (*f)(void), char* name )
{
	if (f() == 0)
		printf("\e[0;32m%s: OK\n\e[0m", name);
	else
		printf("\e[0;31m%s: FAIL\n\e[0m", name);
}

static int	aux_mat4_equal(t_mat4 m1, t_mat4 m2)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (fabs(m1.m[i][j] - m2.m[i][j]) > EPSILON)
				return (0);
		}
	}
	return (1);
}

static void	aux_print_mat4(t_mat4 mat)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%f ", mat.m[i][j]);
		}
		printf("\n");
	}
}

static int	aux_vector_equal(t_vector v1, t_vector v2)
{
	return (fabs(v1.x - v2.x) < EPSILON && fabs(v1.y - v2.y) < EPSILON && fabs(v1.z - v2.z) < EPSILON);
}

static int test_sphere_get_inverse_mat4(void)
{
    return (1);
}

static int test_plane_get_inverse_mat4(void)
{
    return (1);
}

int test_cylinder_get_inverse_mat4(void)
{
    return (1);
}

int main(void)
{
	int (*tests[])(void) = {
		test_sphere_get_inverse_mat4,
		test_plane_get_inverse_mat4,
		test_cylinder_get_inverse_mat4,
	};
	char* test_names[] = {
		"test_sphere_get_inverse_mat4",
		"test_plane_get_inverse_mat4",
		"test_cylinder_get_inverse_mat4",
	};
	print_header();
	for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
		test_function(tests[i], test_names[i]);
	return (0);
}
