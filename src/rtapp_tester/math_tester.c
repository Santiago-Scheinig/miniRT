/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tester.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:54:48 by aramos-r          #+#    #+#             */
/*   Updated: 2026/03/29 20:14:00 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"
#include <stdio.h>

static void    test_function( int (*f)(void), char* name )
{
	if (f() == 0)
		printf("%s: OK\n", name);
	else
		printf("%s: FAIL\n", name);
}

static int    test_vector_new(void)
{
	t_vector v = vector_new(1.0, 2.0, 3.0);
	if (v.x == 1.0 && v.y == 2.0 && v.z == 3.0)
		return (0);
	else
		return (1);
}

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

static int   test_vector_sum_vector(void)
{
	t_vector v1 = vector_new(1.0, 2.0, 3.0);
	t_vector v2 = vector_new(4.0, 5.0, 6.0);
	t_vector result = vector_sum_vector(v1, v2);
	if (result.x == 5.0 && result.y == 7.0 && result.z == 9.0)
		return (0);
	else
		return (1);
}

static int   test_vector_sub_vector(void)
{
	t_vector v1 = vector_new(4.0, 5.0, 1.0);
	t_vector v2 = vector_new(1.0, 2.0, 3.0);
	t_vector result = vector_sub_vector(v1, v2);
	if (!(result.x == 3.0 && result.y == 3.0 && result.z == -2.0))
		return (1);
	return (0);
}

static int  test_vector_module(void)
{
	t_vector v;
	double res;
	
	v = vector_new(3.0, 4.0, 0.0);
	res = vector_module(v);
   if (res != 5.0)
		return (1);
	v = vector_new(0.0, 0.0, 0.0);
	res = vector_module(v);
	if (res != 0.0)
		return (1);
	v = vector_new(-1.0, -2.0, -2.0);
	res = vector_module(v);
	if (res != 3.0)
		return (1);
	return (0);
}

static int test_vector_normalize(void)
{
	t_vector v;
	t_vector res;
	
	v = vector_new(3.0, 4.0, 0.0);
	res = vector_normalize(v);
	if (res.x != 0.6 || res.y != 0.8 || res.z != 0.0)
		return (1);
	v = vector_new(0.0, 0.0, 0.0);
	res = vector_normalize(v);
	if (res.x != 0.0 || res.y != 0.0 || res.z != 0.0)
		return (1);
	v = vector_new(-1.0, -2.0, -2.0);
	res = vector_normalize(v);
	if (res.x != -1.0/3.0 || res.y != -2.0/3.0 || res.z != -2.0/3.0)
		return (1);
	return (0);
}

static int  test_vector_distance_points(void)
{
	t_vector p1 = vector_new(1.0, 2.0, 3.0);
	t_vector p2 = vector_new(4.0, 6.0, 3.0);
	double res = vector_distance_points(p1, p2);
	if (res != 5.0)
		return (1);
	p1 = vector_new(0.0, 0.0, 0.0);
	p2 = vector_new(1.0, 1.0, 1.0);
	res = vector_distance_points(p1, p2);
	if (res != sqrt(3))
		return (1);
	p1 = vector_new(-1.0, -2.0, -3.0);
	res = vector_distance_points(p1, p1);
	if (res != 0.0)
		return (1);
	p1 = vector_new(0.0, 0.0, 0.0);
	res = vector_distance_points(p1, p1);
	if (res != 0.0)
		return (1);
	return (0);
}

static int  test_vector_dot_product(void)
{
	t_vector v1 = vector_new(1.0, 2.0, 3.0);
	t_vector v2 = vector_new(4.0, 5.0, 6.0);
	double res = vector_dot_product(v1, v2);
	if (res != 32.0)
		return (1);
	v1 = vector_new(0.0, 0.0, 0.0);
	res = vector_dot_product(v1, v2);
	if (res != 0.0)
		return (1);
	v1 = vector_new(-1.0, -2.0, -3.0);
	res = vector_dot_product(v1, v2);
	if (res != -32.0)
		return (1);
	return (0);
}

static int  test_vector_cross_product(void)
{
	t_vector v1 = vector_new(1.0, 2.0, 3.0);
	t_vector v2 = vector_new(4.0, 5.0, 6.0);
	t_vector res = vector_cross_product(v1, v2);
	double  res_dot_1 = vector_dot_product(res, v1);
	double  res_dot_2 = vector_dot_product(res, v2);
	if (res.x != -3.0 || res.y != 6.0 || res.z != -3.0 || res_dot_1 != 0.0 || res_dot_2 != 0.0)
		return (1);
	v1 = vector_new(0.0, 0.0, 0.0);
	res = vector_cross_product(v1, v2);
	res_dot_1 = vector_dot_product(res, v1);
	res_dot_2 = vector_dot_product(res, v2);
	if (res.x != 0.0 || res.y != 0.0 || res.z != 0.0 || res_dot_1 != 0.0 || res_dot_2 != 0.0)
		return (1);
	v1 = vector_new(-1.0, -2.0, -3.0);
	res = vector_cross_product(v1, v2);
	res_dot_1 = vector_dot_product(res, v1);
	res_dot_2 = vector_dot_product(res, v2);
	if (res.x != 3.0 || res.y != -6.0 || res.z != 3.0 || res_dot_1 != 0.0 || res_dot_2 != 0.0)
		return (1);
	return (0);
}

static int  test_matrix_new_identity(void)
{
	t_mat4 m = matrix_new_identity();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j && m.m[i][j] != 1.0)
				return (1);
			else if (i != j && m.m[i][j] != 0.0)
				return (1);
		}
	}
	return (0);
}

static int  test_matrix_transpose(void)
{
	t_mat4	og;
	t_mat4	transposed;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++){
			og.m[i][j] = i * 4 + j + 1;
		}
	}
	transposed = matrix_transposed(og);
	if (transposed.m[0][0] != 1.0
		|| transposed.m[0][1] != 5.0
		|| transposed.m[0][2] != 9.0
		|| transposed.m[0][3] != 13.0
		|| transposed.m[1][0] != 2.0
		|| transposed.m[1][1] != 6.0
		|| transposed.m[1][2] != 10.0
		|| transposed.m[1][3] != 14.0
		|| transposed.m[2][0] != 3.0
		|| transposed.m[2][1] != 7.0
		|| transposed.m[2][2] != 11.0
		|| transposed.m[2][3] != 15.0
		|| transposed.m[3][0] != 4.0
		|| transposed.m[3][1] != 8.0
		|| transposed.m[3][2] != 12.0
		|| transposed.m[3][3] != 16.0
	)
		return (1);
	return (0);
}

int main(void)
{
	int (*tests[])(void) = {
		test_vector_new,
		test_vector_mult_scalar,
		test_vector_div_scalar,
		test_vector_sum_vector,
		test_vector_sub_vector,
		test_vector_module,
		test_vector_normalize,
		test_vector_distance_points,
		test_vector_dot_product,
		test_vector_cross_product,
		test_matrix_new_identity,
		test_matrix_transpose,
	};
	char* test_names[] = {
		"test_vector_new",
		"test_vector_mult_scalar",
		"test_vector_div_scalar",
		"test_vector_sum_vector",
		"test_vector_sub_vector",
		"test_vector_module",
		"test_vector_normalize",
		"test_vector_distance_points",
		"test_vector_dot_product",
		"test_vector_cross_product",
		"test_matrix_new_identity",
		"test_matrix_transpose",
	};
	for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
		test_function(tests[i], test_names[i]);
	return (0);
}
