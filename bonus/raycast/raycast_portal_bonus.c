/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_portal_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:10:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/25 16:18:31 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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
void	portal(t_data *data, t_raycast *rc, int from, int deep)
{
	t_raycast	test;
	double		portal_x;
	// t_portal	*portal;
	int			to;

	to = (from + 1) % 2;
	if (rc->side == 0)
		rc->portal_first_ray += (rc->side_dist.x - rc->delta_dist.x);
	else
		rc->portal_first_ray += (rc->side_dist.y - rc->delta_dist.y);
	test = *rc;
	if (rc->side == 0)
		portal_x = rc->player.pos.y + (rc->side_dist.x - rc->delta_dist.x) * rc->ray_dir.y - rc->player.portal[from].pos.y;
	else
		portal_x = rc->player.pos.x + (rc->side_dist.y - rc->delta_dist.y) * rc->ray_dir.x - rc->player.portal[from].pos.x;
	if (!rc->player.portal[to].dir.x)
	{
		test.player.pos.x = rc->player.portal[to].pos.x + find_sign1(rc->player.portal[to], rc->player.portal[from], portal_x);
		if (rc->player.portal[to].dir.y < 0)
			test.player.pos.y = rc->player.portal[to].pos.y + rc->player.portal[to].dir.y * 0.1;
		else
			test.player.pos.y = rc->player.portal[to].pos.y + rc->player.portal[to].dir.y;
	}
	else
	{
		if (rc->player.portal[to].dir.x < 0)
			test.player.pos.x = rc->player.portal[to].pos.x + rc->player.portal[to].dir.x * 0.1;
		else
			test.player.pos.x = rc->player.portal[to].pos.x + rc->player.portal[to].dir.x;
		test.player.pos.y = rc->player.portal[to].pos.y + find_sign2(rc->player.portal[to], rc->player.portal[from], portal_x);
	}
	rotate_vector(&test.ray_dir, &rc->player.portal[from].dir, &rc->player.portal[to].dir);
	test.player.dir = test.ray_dir;
	test.player.plane.x = 0;
	test.player.plane.y = 0;
	cast_a_ray(data, &test, deep);
	if (test.print == false)
		print_ray(data, &test);
	rc->t = data->portal[2 + from];
	if (rc->side == 0)
		rc->portal_first_ray -= (rc->side_dist.x - rc->delta_dist.x);
	else
		rc->portal_first_ray -= (rc->side_dist.y - rc->delta_dist.y);
	print_ray(data, rc);
	rc->print = true;
}
