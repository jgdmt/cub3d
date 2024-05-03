/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_portal_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:10:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/03 11:09:53 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static	double	find_sign1(t_portal to, t_portal from, double portal)
{
	if (to.dir.y == from.dir.x)
		return (portal);
	if (to.dir.y == -from.dir.y)
		return (portal);
	return (1 - portal);
}

static	double	find_sign2(t_portal to, t_portal from, double portal)
{
	if (to.dir.x == from.dir.y)
		return (portal);
	if (to.dir.x == -from.dir.x)
		return (portal);
	return (1 - portal);
}

static	void	init_cam(t_player *cam, t_raycast *rc, int from, double delta)
{
	t_portal	*pl;
	int			to;

	pl = rc->player.portal;
	to = (from + 1) % 2;
	cam->plane.x = 0;
	cam->plane.y = 0;
	if (!pl[to].dir.x)
	{
		cam->pos.x = pl[to].pos.x + find_sign1(pl[to], pl[from], delta);
		if (pl[to].dir.y < 0)
			cam->pos.y = pl[to].pos.y + pl[to].dir.y * 0.1;
		else
			cam->pos.y = pl[to].pos.y + pl[to].dir.y;
	}
	else
	{
		cam->pos.y = pl[to].pos.y + find_sign2(pl[to], pl[from], delta);
		if (pl[to].dir.x < 0)
			cam->pos.x = pl[to].pos.x + pl[to].dir.x * 0.1;
		else
			cam->pos.x = pl[to].pos.x + pl[to].dir.x;
	}
	rot_vector(&cam->dir, &pl[from].dir, &pl[to].dir);
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
	t_raycast	cam;
	double		delta;

	if (rc->side == 0)
	{
		delta = rc->player.pos.y + (rc->side_dist.x - rc->delta_dist.x) * rc->ray_dir.y - rc->player.portal[from].pos.y;
		rc->portal_first_ray += (rc->side_dist.x - rc->delta_dist.x);
	}
	else
	{
		delta = rc->player.pos.x + (rc->side_dist.y - rc->delta_dist.y) * rc->ray_dir.x - rc->player.portal[from].pos.x;
		rc->portal_first_ray += (rc->side_dist.y - rc->delta_dist.y);
	}
	cam = *rc;
	cam.player.dir = cam.ray_dir;
	init_cam(&cam.player, rc, from, delta);
	cast_a_ray(data, &cam, deep);
	if (cam.print == false)
		print_ray(data, &cam);
	rc->t = data->portal[2 + from];
	if (rc->side == 0)
		rc->portal_first_ray -= (rc->side_dist.x - rc->delta_dist.x);
	else
		rc->portal_first_ray -= (rc->side_dist.y - rc->delta_dist.y);
	print_ray(data, rc);
	rc->print = true;
}
