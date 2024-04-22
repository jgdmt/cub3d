/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_portal_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:10:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/22 16:10:21 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief Takes 3 vectors a rotate the first by the angle of the two others.
 * The angle between p1 and p2 need to be a multiple of 90(180, 360).
 * 
 * @param v1 the vector to be rotated
 * @param p1 the first reference vector
 * @param p2 the second reference vector
 */
void	rotate_vector(t_vector *v1, t_int_vector *p1, t_int_vector *p2)
{
	t_vector	temp;

	if (p1->x == p2->x && p1->y == p2->y)
	{
		v1->x = -v1->x;
		v1->y = -v1->y;
	}
	else if (p2->x == p1->y && p2->y == -p1->x)
	{
		temp = *v1;
		v1->x = -temp.y;
		v1->y = temp.x;
	}
	else if (p2->x == -p1->y && p2->y == p1->x)
	{
		temp = *v1;
		v1->x = temp.y;
		v1->y = -temp.x;
	}
}

double	find_sign1(t_portal to, t_portal from, double portal)
{
	if (to.dir.y == from.dir.x)
		return (portal);
	if (to.dir.y == -from.dir.y)
		return (portal);
	return (1 - portal);
}

double	find_sign2(t_portal to, t_portal from, double portal)
{
	if (to.dir.x == from.dir.y)
		return (portal);
	if (to.dir.x == -from.dir.x)
		return (portal);
	return (1 - portal);
}

/**
 * @brief Calculate recursively raypath of a ray from the outgoing portal.
 * Could it recursively a portal inside of a portal.
 * 
 * @param data structure with all program data
 * @param rc structure that store all raycast parameters
 * @param from array value of incoming portal
 * @param to array value of outgoing portal
 */
void	portal(t_data *data, t_raycast *rc, int from, int to, int deep)
{
	t_raycast	test;
	double		portal;

	if (rc->side == 0)
		rc->portal_first_ray = (rc->side_dist.x - rc->delta_dist.x);
	else
		rc->portal_first_ray = (rc->side_dist.y - rc->delta_dist.y);
	if (rc->side == 0)
		portal = rc->player.pos.y + rc->portal_first_ray * rc->ray_dir.y - rc->player.portal[from].pos.y;
	else
		portal = rc->player.pos.x + rc->portal_first_ray * rc->ray_dir.x - rc->player.portal[from].pos.x;
	test = *rc;
	if (!rc->player.portal[to].dir.x)
	{
		test.player.pos.x = rc->player.portal[to].pos.x + find_sign1(rc->player.portal[to], rc->player.portal[from], portal);
		if (rc->player.portal[to].dir.y < 0)
			test.player.pos.y = rc->player.portal[to].pos.y + rc->player.portal[to].dir.y * 0.1;
		else
			test.player.pos.y = rc->player.portal[to].pos.y + rc->player.portal[to].dir.y;
	// printf("x : %lf, y : %lf\n", test.player.pos.x, test.player.pos.y);
	}
	else
	{
		if (rc->player.portal[to].dir.x < 0)
			test.player.pos.x = rc->player.portal[to].pos.x + rc->player.portal[to].dir.x * 0.1;
		else
			test.player.pos.x = rc->player.portal[to].pos.x + rc->player.portal[to].dir.x;
		test.player.pos.y = rc->player.portal[to].pos.y + find_sign2(rc->player.portal[to], rc->player.portal[from], portal);
	}
	rotate_vector(&test.ray_dir, &rc->player.portal[from].dir, &rc->player.portal[to].dir);
	test.portal_first_ray = 0;
	test.player.dir = test.ray_dir;
	test.player.plane.x = 0;
	test.player.plane.y = 0;
	// printf("olddir : (%lf, %lf), plane : (%lf, %lf), pos : (%lf, %lf)\n", rc->ray_dir.x, rc->ray_dir.y, rc->player.plane.x, rc->player.plane.y, rc->player.pos.x, rc->player.pos.y);
	// printf("dir : (%lf, %lf), plane : (%lf, %lf), pos : (%lf, %lf)\n", test.player.dir.x, test.player.dir.y, test.player.plane.x, test.player.plane.y, test.player.pos.x, test.player.pos.y);
	init_ray_param(data->width, &test);
	step_init(&test);
	dda(data, &test, deep);
	get_tex_ptr(data, &test);
	// test.player = rc->player;
	test.portal_first_ray += rc->portal_first_ray;
	*rc = test;
}
