/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_portal_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:10:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/17 18:21:09 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	rotate_vector(t_vector *v1, t_int_vector *p1, t_int_vector *p2)
{
	t_vector	temp;

	// if (p1->x == -p2->x || p1->y == -p2->y)
	// 	return ;
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

void	portal(t_data *data, t_raycast *rc, int from, int to)
{
	t_raycast	test;
	double		portal;

	if (rc->side == 0)
		rc->portal_first_ray = (rc->side_dist.x - rc->delta_dist.x);
	else
		rc->portal_first_ray = (rc->side_dist.y - rc->delta_dist.y);
	if (rc->side == 0)
		portal = (rc->player.pos.y + rc->portal_first_ray * rc->ray_dir.y) - rc->player.portal[from].pos.y;
	else
		portal = ((rc->player.pos.x + rc->portal_first_ray * rc->ray_dir.x)) - rc->player.portal[from].pos.x;
	test = *rc;
	if (!rc->player.portal[to].dir.x)
	{
		test.player.pos.x = rc->player.portal[to].pos.x + portal;
		test.player.pos.y = rc->player.portal[to].pos.y + rc->player.portal[to].dir.y;
	}
	else
	{
		test.player.pos.x = rc->player.portal[to].pos.x + rc->player.portal[to].dir.x;
		test.player.pos.y = rc->player.portal[to].pos.y + portal;
	}
	rotate_vector(&test.ray_dir, &rc->player.portal[from].dir, &rc->player.portal[to].dir);
	rotate_vector(&test.player.plane, &rc->player.portal[from].dir, &rc->player.portal[to].dir);
	test.portal_first_ray = 0;
	test.player.dir = test.ray_dir;
	test.player.plane.x = 1;
	test.player.plane.y = 1;
	printf("perpendicular : %s\n", (test.player.portal[to].dir.x * test.player.plane.x) + (test.player.portal[to].dir.y * test.player.plane.y)? "no": "ok" );
	printf("dir : (%lf, %lf), plane : (%lf, %lf), pos : (%lf, %lf)\n", test.player.dir.x, test.player.dir.y, test.player.plane.x, test.player.plane.y, test.player.pos.x, test.player.pos.y);
	init_ray_param(data->width, &test);
	step_init(&test);
	dda(data, &test);
	get_tex_ptr(data, &test);
	// test.player = rc->player;
	test.portal_first_ray += rc->portal_first_ray;
	*rc = test;
}
