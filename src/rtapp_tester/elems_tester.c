/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:58:29 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/02 20:38:39 by aramos-r         ###   ########.fr       */
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

static int  test_plane_get_inverse_mat4(void)
{
    // Test rayo con origen y direccion
    t_elem_plane plane;
    t_mat4      res;
    t_vector    origen;
    t_vector    origen_res;
    t_vector    exp_orig;
    t_vector    dir;
    t_vector    dir_res;
    t_vector    exp_dir;
    
    plane.normal = vector_new(1.0, 0.0, 0.0);
    plane.pos = vector_new(0.0, 5.0, 0.0);
    plane.rgb = 0xFFFFFF;
    
    res = plane_get_inverse_mat4(plane.pos, plane.normal);
    
    origen = vector_new(0.0, 5.0, 0.0);
    dir = vector_new(1.0, 0.0, 0.0);
    
    origen_res = vector_mult_mat4_point(origen, res);
    dir_res = vector_mult_mat4_dir(dir, res);
    
    exp_orig = vector_new(0.0, 0.0, 0.0);
    exp_dir = vector_new(0.0, 1.0, 0.0);
    
    if (!aux_vector_equal(dir_res, exp_dir))
        return (1);
    if (!aux_vector_equal(origen_res, exp_orig))
        return (1);

    // Test rayo con origen coplanar
    t_vector    origen_coplanar;
    t_vector    origen_coplanar_res;
    t_vector    exp_origen_coplanar;
    t_mat4      mat;
    t_vector    normal_mat;
    t_vector    point_mat;

    normal_mat = vector_new(0.0, 1.0, 0.0);
    point_mat = vector_new(0.0, 5.0, 0.0);
    origen_coplanar = vector_new(0.0, 5.0, 1.0);
    exp_origen_coplanar = vector_new(1.0, 0.0, 0.0);
    mat = plane_get_inverse_mat4(point_mat, normal_mat);

    origen_coplanar_res = vector_mult_mat4_point(origen_coplanar, mat);
    if (!aux_vector_equal(origen_coplanar_res, exp_origen_coplanar))
        return (1);
    return (0);
}

static int test_sphere_get_inverse_mat4(void)
{
    t_vector    center;
    double      diameter;
    t_mat4      matrix;
    t_vector    p1;
    t_vector    p1_exp;
    t_vector    p1_res;
    t_vector    p2;
    t_vector    p2_exp;
    t_vector    p2_res;
    t_vector    p3;
    t_vector    p3_exp;
    t_vector    p3_res;
    t_vector    p4;
    t_vector    p4_exp;
    t_vector    p4_res;

    center = vector_new(10.0, 0.0, 0.0);
    diameter = 4.0;
    matrix = sphere_get_inverse_mat4(center, diameter);

    p1 = vector_new(10.0, 0.0, 0.0);
    p1_exp = vector_new(0.0, 0.0, 0.0);
    p1_res = vector_mult_mat4_point(p1, matrix);
    if (!aux_vector_equal(p1_res, p1_exp))
        return (1);

    p2 = vector_new(12.0, 0.0, 0.0);
    p2_exp = vector_new(1.0, 0.0, 0.0);
    p2_res = vector_mult_mat4_point(p2, matrix);
    if (!aux_vector_equal(p2_res, p2_exp))
        return (1);

    p3 = vector_new(10.0, -2.0, 0.0);
    p3_exp = vector_new(0.0, -1.0, 0.0);
    p3_res = vector_mult_mat4_point(p3, matrix);
    if (!aux_vector_equal(p3_res, p3_exp))
        return (1);
    p4 = vector_new(10.0, 0.0, 2.0);
    p4_exp = vector_new(0.0, 0.0, 1.0);
    p4_res = vector_mult_mat4_point(p4, matrix);
    if (!aux_vector_equal(p4_res, p4_exp))
        return (1);
    return (0);
}

int test_cylinder_get_inverse_mat4(void)
{
    t_vector    center;
    double      diameter;
    t_vector    normal;
    double      height;
    t_mat4      matrix;
    t_vector    p1;
    t_vector    p1_exp;
    t_vector    p1_res;
    t_vector    p2;
    t_vector    p2_exp;
    t_vector    p2_res;
    t_vector    p3;
    t_vector    p3_exp;
    t_vector    p3_res;

    center = vector_new(0.0, 10.0, 0.0);
    diameter = 2.0;
    normal = vector_new(0.0, 1.0, 0.0);
    height = 5.0;

    matrix = cylinder_get_inverse_mat4(center, diameter, normal, height);
    
    p1 = vector_new(0.0, 10.0, 0.0);
    p1_exp = vector_new(0.0, 0.0, 0.0);
    p1_res = vector_mult_mat4_point(p1, matrix);

    if (!aux_vector_equal(p1_res, p1_exp))
        return (1);
    
    p2 = vector_new(1.0, 10.0, 0.0);
    p2_exp = vector_new(0.0, 0.0, -1.0);
    p2_res = vector_mult_mat4_point(p2, matrix);

    if (!aux_vector_equal(p2_res, p2_exp))
        return (1);
    
    p3 = vector_new(0.0, 12.5, 0.0);
    p3_exp = vector_new(0.0, 1.0, 0.0);
    p3_res = vector_mult_mat4_point(p3, matrix);
    if (!aux_vector_equal(p3_res, p3_exp))
        return (1);
    return (0);
}

static int  test_plane_intersection(void)
{
    t_elem_plane    plane;
    t_ray           ray;
    t_ray           local_ray;
    double          res;
    
    plane.normal = vector_new(0.0, 1.0, 0.0);
    plane.pos = vector_new(0.0, 5.0, 0.0);
    plane.rgb = 0xFFFFFF;

    ray.origin = vector_new(0.0, 0.0, 0.0);
    ray.direction = vector_new(0.0, 1.0, 1.0);
    ray.direction = vector_normalize(ray.direction);
    local_ray = ray_transform(ray, plane_get_inverse_mat4(plane.pos, plane.normal));
    res = plane_intersection(local_ray, &plane);
    if (fabs(res - sqrt(50.0)) > EPSILON)
        return (1);
    return (0);
}

static int  test_sphere_intersection(void)
{
    t_ray           ray;
    t_ray           local_ray;
    double          res;
    t_vector        center;
    double          diameter;
    
    ray.origin = vector_new(0.0, 0.0, 0.0);
    ray.direction = vector_new(1.0, 0.0, 1.0);
    ray.direction = vector_normalize(ray.direction);
    center = vector_new(5.0, 0.0, 0.0);
    diameter = 2.0;
    local_ray = ray_transform(ray, sphere_get_inverse_mat4(center, diameter));
    res = sphere_intersection(local_ray, NULL);
    if (res - INFINITY > EPSILON)
        return (1);
    center.z = 4.8;
    local_ray = ray_transform(ray, sphere_get_inverse_mat4(center, diameter));
    res = sphere_intersection(local_ray, NULL);
    if (fabs(res - sqrt((4.2 * 4.2 ) + (4.2 * 4.2))) > EPSILON)
        return (1);
    return (0);
}

int main(void)
{
	int (*tests[])(void) = {
		test_plane_get_inverse_mat4,
		test_sphere_get_inverse_mat4,
		test_cylinder_get_inverse_mat4,
        test_plane_intersection,
        test_sphere_intersection
	};
	char* test_names[] = {
		"test_plane_get_inverse_mat4",
		"test_sphere_get_inverse_mat4",
		"test_cylinder_get_inverse_mat4",
        "test_plane_intersection",
        "test_sphere_intersection"
	};
	print_header();
	for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
		test_function(tests[i], test_names[i]);
	return (0);
}
