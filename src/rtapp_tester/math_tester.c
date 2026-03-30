/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tester.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:54:48 by aramos-r          #+#    #+#             */
/*   Updated: 2026/03/30 19:54:37 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmth.h"
#include <stdio.h>

static void	print_header(void)
{
	printf("\e[1;34m====================\n");
	printf("   MATH TESTER\n");
	printf("====================\e[0m\n");
}

static void	test_function( int (*f)(void), char* name )
{
	if (f() == 0)
		printf("\e[0;32m%s: OK\n\e[0m", name);
	else
		printf("\e[0;31m%s: FAIL\n\e[0m", name);
}

static int	test_vector_new(void)
{
	t_vector v = vector_new(1.0, 2.0, 3.0);
	if (v.x == 1.0 && v.y == 2.0 && v.z == 3.0)
		return (0);
	else
		return (1);
}

static int	test_vector_mult_scalar(void)
{
	t_vector v = vector_new(1.0, 2.0, 3.0);
	t_vector result = vector_mult_scalar(v, 2.0);
	if (result.x == 2.0 && result.y == 4.0 && result.z == 6.0)
		return (0);
	else
		return (1);
}

static int	test_vector_div_scalar(void)
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

static int	test_vector_sum_vector(void)
{
	t_vector v1 = vector_new(1.0, 2.0, 3.0);
	t_vector v2 = vector_new(4.0, 5.0, 6.0);
	t_vector result = vector_sum_vector(v1, v2);
	if (result.x == 5.0 && result.y == 7.0 && result.z == 9.0)
		return (0);
	else
		return (1);
}

static int	test_vector_sub_vector(void)
{
	t_vector v1 = vector_new(4.0, 5.0, 1.0);
	t_vector v2 = vector_new(1.0, 2.0, 3.0);
	t_vector result = vector_sub_vector(v1, v2);
	if (!(result.x == 3.0 && result.y == 3.0 && result.z == -2.0))
		return (1);
	return (0);
}

static int	test_vector_module(void)
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

static int	test_vector_normalize(void)
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

static int	test_vector_distance_points(void)
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

static int	test_vector_dot_product(void)
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

static int	test_vector_cross_product(void)
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

static int	test_mat4_new_identity(void)
{
	t_mat4 m = mat4_new_identity();
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

static int	test_mat4_transpose(void)
{
	t_mat4	og;
	t_mat4	transposed;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++){
			og.m[i][j] = i * 4 + j + 1;
		}
	}
	transposed = mat4_transposed(og);
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

static int	test_mat4_determinant(void)
{
	t_mat4 m;
	m.m[0][0] = 1.0; m.m[0][1] = 2.0; m.m[0][2] = 3.0; m.m[0][3] = 4.0;
	m.m[1][0] = 5.0; m.m[1][1] = 6.0; m.m[1][2] = 7.0; m.m[1][3] = 8.0;
	m.m[2][0] = 9.0; m.m[2][1] = 10.0; m.m[2][2] = 11.0; m.m[2][3] = 12.0;
	m.m[3][0] = 13.0; m.m[3][1] = 14.0; m.m[3][2] = 15.0; m.m[3][3] = 16.0;
	double res = mat4_determinant(m);
	if (res != 0.0)
		return (1);
	m.m[0][0] = 5.0; m.m[0][1] = 7.0; m.m[0][2] = 9.0; m.m[0][3] = 0.0;
	m.m[1][0] = 4.0; m.m[1][1] = 9.0; m.m[1][2] = 6.0; m.m[1][3] = 7.0;
	m.m[2][0] = 1.0; m.m[2][1] = 6.0; m.m[2][2] = 3.0; m.m[2][3] = 5.0;
	m.m[3][0] = 8.0; m.m[3][1] = 6.0; m.m[3][2] = 7.0; m.m[3][3] = 8.0;
	res = mat4_determinant(m);
	if (res != 196.0)
		return (1);
	return (0);
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

static int	test_mat4_inverse(void)
{
	t_mat4 m;
	m.m[0][0] = 1.0; m.m[0][1] = 2.0; m.m[0][2] = 3.0; m.m[0][3] = 4.0;
	m.m[1][0] = 5.0; m.m[1][1] = 6.0; m.m[1][2] = 7.0; m.m[1][3] = 8.0;
	m.m[2][0] = 9.0; m.m[2][1] = 10.0; m.m[2][2] = 11.0; m.m[2][3] = 12.0;
	m.m[3][0] = 13.0; m.m[3][1] = 14.0; m.m[3][2] = 15.0; m.m[3][3] = 16.0;
	t_mat4 inverse = mat4_inverse(m);
	if (!aux_mat4_equal(inverse, mat4_new_identity()))
		return (1);
	m.m[0][0] = 5.0; m.m[0][1] = 7.0; m.m[0][2] = 9.0; m.m[0][3] = 0.0;
	m.m[1][0] = 4.0; m.m[1][1] = 9.0; m.m[1][2] = 6.0; m.m[1][3] = 7.0;
	m.m[2][0] = 1.0; m.m[2][1] = 6.0; m.m[2][2] = 3.0; m.m[2][3] = 5.0;
	m.m[3][0] = 8.0; m.m[3][1] = 6.0; m.m[3][2] = 7.0; m.m[3][3] = 8.0;
	inverse = mat4_inverse(m);
	t_mat4 exp;
	exp.m[0][0] = -39.0/196; exp.m[0][1] = 239.0/196; exp.m[0][2] = -277.0/196; exp.m[0][3] = -9.0/49;
	exp.m[1][0] = -29.0/196; exp.m[1][1] = 233.0/196; exp.m[1][2] = -211.0/196; exp.m[1][3] = -18.0/49;
	exp.m[2][0] = 33.0/98; exp.m[2][1] = -157.0/98; exp.m[2][2] = 159.0/98; exp.m[2][3] = 19.0/49;
	exp.m[3][0] = 3.0/196; exp.m[3][1] = -139.0/196; exp.m[3][2] = 157.0/196; exp.m[3][3] = 12.0/49;
	if (!aux_mat4_equal(inverse, exp))
		return (1);
	return (0);
}

static int	test_mat4_mult_mat4(void)
{
	t_mat4 m1;
	m1.m[0][0] = 1.0; m1.m[0][1] = 2.0; m1.m[0][2] = 3.0; m1.m[0][3] = 4.0;
	m1.m[1][0] = 5.0; m1.m[1][1] = 6.0; m1.m[1][2] = 7.0; m1.m[1][3] = 8.0;
	m1.m[2][0] = 9.0; m1.m[2][1] = 10.0; m1.m[2][2] = 11.0; m1.m[2][3] = 12.0;
	m1.m[3][0] = 13.0; m1.m[3][1] = 14.0; m1.m[3][2] = 15.0; m1.m[3][3] = 16.0;
	t_mat4 res = mat4_mult_mat4(m1, mat4_new_identity());
	if (!aux_mat4_equal(res, m1))
		return (1);
	t_mat4 m2;
	m2.m[0][0] = 5.0; m2.m[0][1] = 7.0; m2.m[0][2] = 9.0; m2.m[0][3] = 0.0;
	m2.m[1][0] = 4.0; m2.m[1][1] = 9.0; m2.m[1][2] = 6.0; m2.m[1][3] = 7.0;
	m2.m[2][0] = 1.0; m2.m[2][1] = 6.0; m2.m[2][2] = 3.0; m2.m[2][3] = 5.0;
	m2.m[3][0] = 8.0; m2.m[3][1] = 6.0; m2.m[3][2] = 7.0; m2.m[3][3] = 8.0;
	res = mat4_mult_mat4(m1, m2);
	t_mat4 exp;
	exp.m[0][0] = 48.0; exp.m[0][1] = 67.0; exp.m[0][2] = 58.0; exp.m[0][3] = 61.0;
	exp.m[1][0] = 120.0; exp.m[1][1] = 179.0; exp.m[1][2] = 158.0; exp.m[1][3] = 141.0;
	exp.m[2][0] = 192.0; exp.m[2][1] = 291.0; exp.m[2][2] = 258.0; exp.m[2][3] = 221.0;
	exp.m[3][0] = 264.0; exp.m[3][1] = 403.0; exp.m[3][2] = 358.0; exp.m[3][3] = 301.0;
	if (!aux_mat4_equal(res, exp))
		return (1);
	return (0);
}

static int	test_mat4_translation(void)
{
	t_mat4 res = mat4_translation(1.0, 2.0, 3.0);
	t_mat4 exp = mat4_new_identity();
	exp.m[0][3] = 1.0;
	exp.m[1][3] = 2.0;
	exp.m[2][3] = 3.0;
	if (!aux_mat4_equal(res, exp))
		return (1);
	return (0);
}

static int	test_mat4_rotation_x(void)
{
	t_mat4 res = mat4_rotation_x(M_PI / 2);
	t_mat4 exp = mat4_new_identity();
	exp.m[1][1] = 0.0;
	exp.m[1][2] = -1.0;
	exp.m[2][1] = 1.0;
	exp.m[2][2] = 0.0;
	if (!aux_mat4_equal(res, exp))
		return (1);
	return (0);
}

static int 	test_mat4_rotation_y(void)
{
	t_mat4 res = mat4_rotation_y(M_PI / 2);
	t_mat4 exp = mat4_new_identity();
	exp.m[0][0] = 0.0;
	exp.m[0][2] = 1.0;
	exp.m[2][0] = -1.0;
	exp.m[2][2] = 0.0;
	if (!aux_mat4_equal(res, exp))
		return (1);
	return (0);
}

static int 	test_mat4_rotation_z(void)
{
	t_mat4 res = mat4_rotation_z(M_PI / 2);
	t_mat4 exp = mat4_new_identity();
	exp.m[0][0] = 0.0;
	exp.m[0][1] = -1.0;
	exp.m[1][0] = 1.0;
	exp.m[1][1] = 0.0;
	if (!aux_mat4_equal(res, exp))
		return (1);
	return (0);
}

static int	test_mat4_scale(void)
{
	t_mat4 res = mat4_scale(2.0, 3.0, 4.0);
	t_mat4 exp = mat4_new_identity();
	exp.m[0][0] = 2.0;
	exp.m[1][1] = 3.0;
	exp.m[2][2] = 4.0;
	if (!aux_mat4_equal(res, exp))
		return (1);
	return (0);
}

static int	test_solve_quadratic(void)
{
	double a = 1.0;
	double b = -3.0;
	double c = 2.0;
	t_roots res = solve_quadratic(a, b, c);
	if (!res.has_solutions || fabs(res.sol1 - 2.0) > EPSILON || fabs(res.sol2 - 1.0) > EPSILON)
		return (1);
	a = 1.0;
	b = 2.0;
	c = 5.0;
	res = solve_quadratic(a, b, c);
	if (res.has_solutions)
		return (1);
	a = 1.0;
	b = -2.0;
	c = 1.0;
	res = solve_quadratic(a, b, c);
	if (!res.has_solutions || fabs(res.sol1 - 1.0) > EPSILON || fabs(res.sol2 - 1.0) > EPSILON || res.sol1 != res.sol2)
		return (1);
	return (0);
}

static int	aux_vector_equal(t_vector v1, t_vector v2)
{
	return (fabs(v1.x - v2.x) < EPSILON && fabs(v1.y - v2.y) < EPSILON && fabs(v1.z - v2.z) < EPSILON);
}

static int	test_ray_new(void)
{
	t_vector origin = vector_new(1.0, 2.0, 3.0);
	t_vector direction = vector_new(2.0, 3.0, 6.0);
	t_ray ray = ray_new(origin, vector_normalize(direction));
	if (!aux_vector_equal(ray.origin, origin) || !aux_vector_equal(ray.direction, vector_normalize(direction)))
		return (1);
	origin = vector_new(1.0, 2.0, 3.0);
	direction = vector_new(0.0, 0.0, 0.0);
	ray = ray_new(origin, vector_normalize(direction));
	if (!aux_vector_equal(ray.origin, origin) || !aux_vector_equal(ray.direction, vector_normalize(direction)))
		return (1);
	return (0);	
}

static int	test_ray_point_at(void)
{
	t_ray ray;
	ray.origin = vector_new(1.0, 2.0, 3.0);
	ray.direction = vector_new(2.0, 3.0, 6.0);
	double t = 2.0;
	t_vector res = ray_point_at(ray, t);
	t_vector exp = vector_new(5.0, 8.0, 15.0);
	if (!aux_vector_equal(res, exp))
		return (1);
	ray.direction = vector_new(0.0, 0.0, 0.0);
	res = ray_point_at(ray, t);
	exp = vector_new(1.0, 2.0, 3.0);
	if (!aux_vector_equal(res, exp))
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
		test_mat4_new_identity,
		test_mat4_transpose,
		test_mat4_determinant,
		test_mat4_inverse,
		test_mat4_mult_mat4,
		test_mat4_translation,
		test_mat4_rotation_x,
		test_mat4_rotation_y,
		test_mat4_rotation_z,
		test_mat4_scale,
		test_solve_quadratic,
		test_ray_new,
		test_ray_point_at,
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
		"test_mat4_new_identity",
		"test_mat4_transpose",
		"test_mat4_determinant",
		"test_mat4_inverse",
		"test_mat4_mult_mat4",
		"test_mat4_translation",
		"test_mat4_rotation_x",
		"test_mat4_rotation_y",
		"test_mat4_rotation_z",
		"test_mat4_scale",
		"test_solve_quadratic",
		"test_ray_new",
		"test_ray_point_at",
	};
	print_header();
	for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
		test_function(tests[i], test_names[i]);
	return (0);
}
