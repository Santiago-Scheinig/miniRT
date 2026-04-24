/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:58:29 by aramos-r          #+#    #+#             */
/*   Updated: 2026/04/24 12:52:15 by aramos-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * NOTE: The previous version of this tester called internal static functions
 * (pl_inv_mat4, sp_inv_mat4, cy_inv_mat4, plane_intersection, sphere_intersection,
 * cylinder_intersection, plane_get_normal, sphere_get_normal, cylinder_get_normal,
 * get_pixel_ray) that have since been made private (static) member functions of
 * their respective object builders.
 *
 * This updated tester uses only the public API:
 *   - build_pl / build_sp / build_cy / build_camera to construct objects
 *   - obj->transform.inv  to verify the inverse matrix
 *   - obj->c_intersection(local_ray) to test intersection
 *   - obj->c_normal(local_point)     to test normal computation
 *   - camera.get_pixel_ray(&camera, x, y) to test ray generation
 *
 * The t_elem_plane struct no longer exists: planes have no data pointer.
 * Cylinder pos/normal are no longer stored in t_elem_cylinder; they are
 * consumed into the transform matrix during build_cy.
 */

#include "rtelm.h"
#include <stdio.h>
#include <math.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

/* ---------- helpers --------------------------------------------------- */

static void	print_header(void)
{
	printf("\e[1;34m====================\n");
	printf("   ELEMS TESTER\n");
	printf("====================\e[0m\n");
}

static void	test_function(int (*f)(void), char *name)
{
	if (f() == 0)
		printf("\e[0;32m%s: OK\n\e[0m", name);
	else
		printf("\e[0;31m%s: FAIL\n\e[0m", name);
}

static int	aux_vector_equal(t_vector v1, t_vector v2)
{
	return (fabs(v1.x - v2.x) < EPSILON
		&& fabs(v1.y - v2.y) < EPSILON
		&& fabs(v1.z - v2.z) < EPSILON);
}

/* ---------- pl_inv_mat4 ------------------------------------------------
 * Verified indirectly: build a plane, then transform a known world-space
 * ray by obj->transform.inv and check it lands in canonical space.
 * --------------------------------------------------------------------- */
static int	test_plane_get_inverse_mat4(void)
{
	t_object	obj;
	t_ray		world_ray;
	t_ray		local_ray;

	/* plane at (0,5,0) facing X → normal (1,0,0) */
	char *str1[] = {"pl", "0.0,5.0,0.0", "1.0,0.0,0.0", "255,255,255", NULL};
	if (build_pl(str1, &obj))
		return (1);

	world_ray.origin    = vector_new(0.0, 5.0, 0.0);
	world_ray.direction = vector_new(1.0, 0.0, 0.0);
	local_ray = ray_transform(world_ray, &obj.transform.inv);

	/* origin should be at (0,0,0) in local space */
	if (!aux_vector_equal(local_ray.origin, vector_new(0.0, 0.0, 0.0)))
		return (1);
	/* direction (1,0,0) aligned with normal → maps to (0,1,0) in local Y */
	if (!aux_vector_equal(local_ray.direction, vector_new(0.0, 1.0, 0.0)))
		return (1);

	/* plane at (0,5,0) facing Y → test a coplanar origin offset in Z */
	char *str2[] = {"pl", "0.0,5.0,0.0", "0.0,1.0,0.0", "255,255,255", NULL};
	if (build_pl(str2, &obj))
		return (1);

	world_ray.origin    = vector_new(0.0, 5.0, 1.0);
	world_ray.direction = vector_new(0.0, 1.0, 0.0);
	local_ray = ray_transform(world_ray, &obj.transform.inv);

	/* coplanar point (0,5,1) → local (1,0,0)  */
	if (!aux_vector_equal(local_ray.origin, vector_new(1.0, 0.0, 0.0)))
		return (1);
	return (0);
}

/* ---------- sp_inv_mat4 ----------------------------------------------- */
static int	test_sphere_get_inverse_mat4(void)
{
	t_object	obj;
	t_vector	p;
	t_vector	res;

	/* sphere at (10,0,0) with diameter 4 */
	char *str[] = {"sp", "10.0,0.0,0.0", "4.0", "255,255,255", NULL};
	if (build_sp(str, &obj))
		return (1);

	/* center maps to (0,0,0) */
	p = vector_new(10.0, 0.0, 0.0);
	res = vector_mult_mat4_point(p, &obj.transform.inv);
	if (!aux_vector_equal(res, vector_new(0.0, 0.0, 0.0)))
		return (1);

	/* surface point +2 on X maps to (1,0,0) */
	p = vector_new(12.0, 0.0, 0.0);
	res = vector_mult_mat4_point(p, &obj.transform.inv);
	if (!aux_vector_equal(res, vector_new(1.0, 0.0, 0.0)))
		return (1);

	/* surface point -2 on Y maps to (0,-1,0) */
	p = vector_new(10.0, -2.0, 0.0);
	res = vector_mult_mat4_point(p, &obj.transform.inv);
	if (!aux_vector_equal(res, vector_new(0.0, -1.0, 0.0)))
		return (1);

	/* surface point +2 on Z maps to (0,0,1) */
	p = vector_new(10.0, 0.0, 2.0);
	res = vector_mult_mat4_point(p, &obj.transform.inv);
	if (!aux_vector_equal(res, vector_new(0.0, 0.0, 1.0)))
		return (1);
	return (0);
}

/* ---------- cy_inv_mat4 ----------------------------------------------- */
static int	test_cylinder_get_inverse_mat4(void)
{
	t_object	obj;
	t_vector	p;
	t_vector	res;

	/* cylinder at (0,10,0), normal (0,1,0), diam 2, height 5 */
	char *str[] = {"cy", "0.0,10.0,0.0", "0.0,1.0,0.0",
		"2.0", "5.0", "255,255,255", NULL};
	if (build_cy(str, &obj))
		return (1);

	/* center (0,10,0) → (0,0,0) */
	p = vector_new(0.0, 10.0, 0.0);
	res = vector_mult_mat4_point(p, &obj.transform.inv);
	if (!aux_vector_equal(res, vector_new(0.0, 0.0, 0.0)))
		return (1);

	/* (1,10,0) → (0,0,-1) — radius=1 in local XZ, rotated by mat4_rotation */
	p = vector_new(1.0, 10.0, 0.0);
	res = vector_mult_mat4_point(p, &obj.transform.inv);
	if (!aux_vector_equal(res, vector_new(0.0, 0.0, -1.0)))
		return (1);

	/* top cap midpoint (0,12.5,0) → (0,1,0) */
	p = vector_new(0.0, 12.5, 0.0);
	res = vector_mult_mat4_point(p, &obj.transform.inv);
	if (!aux_vector_equal(res, vector_new(0.0, 1.0, 0.0)))
		return (1);
	return (0);
}

/* ---------- plane intersection ---------------------------------------- */
static int	test_plane_intersection(void)
{
	t_object	obj;
	t_ray		world_ray;
	t_ray		local_ray;
	double		res;

	/* plane at (0,5,0) facing Y */
	char *str[] = {"pl", "0.0,5.0,0.0", "0.0,1.0,0.0", "255,255,255", NULL};
	if (build_pl(str, &obj))
		return (1);

	world_ray.origin    = vector_new(0.0, 0.0, 0.0);
	world_ray.direction = vector_normalize(vector_new(0.0, 1.0, 1.0));

	local_ray = ray_transform(world_ray, &obj.transform.inv);
	res = obj.c_intersection(local_ray);

	if (fabs(res - sqrt(50.0)) > EPSILON)
		return (1);
	return (0);
}

/* ---------- sphere intersection --------------------------------------- */
static int	test_sphere_intersection(void)
{
	t_object	obj;
	t_ray		world_ray;
	t_ray		local_ray;
	double		res;

	world_ray.origin    = vector_new(0.0, 0.0, 0.0);
	world_ray.direction = vector_normalize(vector_new(1.0, 0.0, 1.0));

	/* sphere at (5,0,0) diam 2 — ray misses */
	char *str1[] = {"sp", "5.0,0.0,0.0", "2.0", "255,255,255", NULL};
	if (build_sp(str1, &obj))
		return (1);
	local_ray = ray_transform(world_ray, &obj.transform.inv);
	res = obj.c_intersection(local_ray);
	if (res != INFINITY)
		return (1);

	/* sphere shifted in Z so ray hits */
	char *str2[] = {"sp", "5.0,0.0,4.8", "2.0", "255,255,255", NULL};
	if (build_sp(str2, &obj))
		return (1);
	local_ray = ray_transform(world_ray, &obj.transform.inv);
	res = obj.c_intersection(local_ray);
	if (fabs(res - sqrt((4.2 * 4.2) + (4.2 * 4.2))) > EPSILON)
		return (1);
	return (0);
}

/* ---------- cylinder intersection ------------------------------------- */
static int	test_cylinder_intersection(void)
{
	t_object	obj;
	t_ray		world_ray;
	t_ray		local_ray;
	double		res;

	world_ray.origin    = vector_new(0.0, 0.0, 0.0);
	world_ray.direction = vector_normalize(vector_new(1.0, 0.0, 1.0));

	/* cylinder at (5,0,-4), normal (0,0,1), diam 4, height 5 — ray misses */
	char *str1[] = {"cy", "5.0,0.0,-4.0", "0.0,0.0,1.0",
		"4.0", "5.0", "255,255,255", NULL};
	if (build_cy(str1, &obj))
		return (1);
	local_ray = ray_transform(world_ray, &obj.transform.inv);
	res = obj.c_intersection(local_ray);
	if (res != INFINITY)
		return (1);

	/* cylinder at (5,0,5.5) — ray hits */
	char *str2[] = {"cy", "5.0,0.0,5.5", "0.0,0.0,1.0",
		"4.0", "5.0", "255,255,255", NULL};
	if (build_cy(str2, &obj))
		return (1);
	local_ray = ray_transform(world_ray, &obj.transform.inv);
	res = obj.c_intersection(local_ray);
	if (fabs(res - 4.242641) > 0.0001)
		return (1);
	return (0);
}

/* ---------- plane normal ---------------------------------------------- */
static int	test_plane_get_normal(void)
{
	t_object	obj;
	t_vector	local_point;
	t_vector	normal;

	char *str[] = {"pl", "0.0,5.0,0.0", "0.0,1.0,0.0", "255,255,255", NULL};
	if (build_pl(str, &obj))
		return (1);

	/* the canonical plane always returns (0,1,0) regardless of local point */
	local_point = vector_new(1.0, 0.0, 1.0);
	normal = obj.c_normal(local_point);
	if (!aux_vector_equal(normal, vector_new(0.0, 1.0, 0.0)))
		return (1);
	return (0);
}

/* ---------- sphere normal --------------------------------------------- */
static int	test_sphere_get_normal(void)
{
	t_object	obj;
	t_vector	local_point;
	t_vector	normal;

	char *str[] = {"sp", "0.0,0.0,0.0", "2.0", "255,255,255", NULL};
	if (build_sp(str, &obj))
		return (1);

	/* for a unit sphere the normal equals the local surface point */
	local_point = vector_new(1.0, 1.0, 1.0);
	normal = obj.c_normal(local_point);
	if (!aux_vector_equal(normal, local_point))
		return (1);
	return (0);
}

/* ---------- cylinder normal ------------------------------------------- */
static int	test_cylinder_get_normal(void)
{
	t_object	obj;
	t_vector	local_point;
	t_vector	normal;
	double		sqrt2;

	char *str[] = {"cy", "0.0,0.0,0.0", "0.0,1.0,0.0",
		"2.0", "2.0", "255,255,255", NULL};
	if (build_cy(str, &obj))
		return (1);

	/* top cap */
	local_point = vector_new(0.0, 1.0, 0.0);
	normal = obj.c_normal(local_point);
	if (!aux_vector_equal(normal, vector_new(0.0, 1.0, 0.0)))
		return (1);

	/* bottom cap */
	local_point = vector_new(0.0, -1.0, 0.0);
	normal = obj.c_normal(local_point);
	if (!aux_vector_equal(normal, vector_new(0.0, -1.0, 0.0)))
		return (1);

	/* side surface */
	sqrt2 = sqrt(0.5);
	local_point = vector_new(sqrt2, 0.5, sqrt2);
	normal = obj.c_normal(local_point);
	if (!aux_vector_equal(normal, vector_new(sqrt2, 0.0, sqrt2)))
		return (1);
	return (0);
}

/* ---------- camera pixel ray ------------------------------------------ */
static int	test_get_pixel_ray(void)
{
	t_elem_camera	camera;
	t_ray			ray;
	t_vector		exp;

	char *str[] = {"C", "0.0,0.0,0.0", "0.0,0.0,-1.0", "90", NULL};
	if (build_camera(str, &camera))
		return (1);

	/* top-left pixel: direction should point left (+) and up (+y), forward (-z) */
	ray = camera.get_pixel_ray(&camera, 0, 0);
	if (!aux_vector_equal(ray.origin, camera.pos))
		return (1);
	if (fabs(vector_module(ray.direction) - 1.0) > EPSILON)
		return (1);
	if (ray.direction.x >= 0.0 || ray.direction.y <= 0.0 || ray.direction.z >= 0.0)
		return (1);

	/* bottom-right pixel */
	ray = camera.get_pixel_ray(&camera, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
	if (!aux_vector_equal(ray.origin, camera.pos))
		return (1);
	if (fabs(vector_module(ray.direction) - 1.0) > EPSILON)
		return (1);
	if (ray.direction.x <= 0.0 || ray.direction.y >= 0.0 || ray.direction.z >= 0.0)
		return (1);

	/* center pixel */
	ray = camera.get_pixel_ray(&camera, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	if (!aux_vector_equal(ray.origin, camera.pos))
		return (1);
	if (fabs(vector_module(ray.direction) - 1.0) > EPSILON)
		return (1);
	exp = vector_new(0.00052, -0.00052, -1.0);
	if (!aux_vector_equal(ray.direction, exp))
		return (1);
	return (0);
}

/* ---------- main ------------------------------------------------------ */
int	main(void)
{
	int (*tests[])(void) = {
		test_plane_get_inverse_mat4,
		test_sphere_get_inverse_mat4,
		test_cylinder_get_inverse_mat4,
		test_plane_intersection,
		test_sphere_intersection,
		test_cylinder_intersection,
		test_plane_get_normal,
		test_sphere_get_normal,
		test_cylinder_get_normal,
		test_get_pixel_ray
	};
	char *test_names[] = {
		"test_plane_get_inverse_mat4",
		"test_sphere_get_inverse_mat4",
		"test_cylinder_get_inverse_mat4",
		"test_plane_intersection",
		"test_sphere_intersection",
		"test_cylinder_intersection",
		"test_plane_get_normal",
		"test_sphere_get_normal",
		"test_cylinder_get_normal",
		"test_get_pixel_ray"
	};
	print_header();
	for (int i = 0; i < (int)(sizeof(tests) / sizeof(tests[0])); i++)
		test_function(tests[i], test_names[i]);
	return (0);
}