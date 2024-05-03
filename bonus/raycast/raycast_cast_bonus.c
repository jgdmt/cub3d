/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_cast_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:25:41 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/03 12:00:58 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief Init all ray parameters inside the rc structure.
 * 
 * @param width of the raycast render image
 * @param rc structure that store all raycast parameters
 */
void	init_ray_param(int width, t_raycast *rc)
{
	double		camera_x;

	camera_x = 2 * rc->x / (double) width - 1;
	rc->ray_dir.x = rc->player.dir.x + rc->player.plane.x * camera_x;
	rc->ray_dir.y = rc->player.dir.y + rc->player.plane.y * camera_x;
	rc->ipos.x = (int)rc->player.pos.x;
	rc->ipos.y = (int)rc->player.pos.y;
	if (rc->ray_dir.x == 0)
		rc->delta_dist.x = 1e30;
	else
		rc->delta_dist.x = fabs(1 / rc->ray_dir.x);
	if (rc->ray_dir.y == 0)
		rc->delta_dist.y = 1e30;
	else
		rc->delta_dist.y = fabs(1 / rc->ray_dir.y);
}

void	step_init( t_raycast *rc)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step.x = -1;
		rc->side_dist.x = (rc->player.pos.x - rc->ipos.x) * rc->delta_dist.x;
	}
	else
	{
		rc->step.x = 1;
		rc->side_dist.x = (rc->ipos.x + 1.0 - rc->player.pos.x)
			* rc->delta_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step.y = -1;
		rc->side_dist.y = (rc->player.pos.y - rc->ipos.y)
			* rc->delta_dist.y;
	}
	else
	{
		rc->step.y = 1;
		rc->side_dist.y = (rc->ipos.y + 1.0 - rc->player.pos.y)
			* rc->delta_dist.y;
	}
}

static void	portal_hit(t_raycast *rc, t_portal *pl, t_data *data, int deep)
{
	if (rc->ipos.y == pl[0].pos.y && rc->ipos.x == pl[0].pos.x \
	&& pl[1].status == 1 && deep < 15)
	{
		if ((pl[0].dir.x && pl[0].dir.x * rc->ray_dir.x < 0 && rc->side == 0) \
		|| (pl[0].dir.y && pl[0].dir.y * rc->ray_dir.y < 0 && rc->side == 1))
		{
			portal(data, rc, 0, ++deep);
			return ;
		}
	}
	if (rc->ipos.y == pl[1].pos.y && rc->ipos.x == pl[1].pos.x \
	&& pl[0].status == 1 && deep < 15)
	{
		if ((pl[1].dir.x && pl[1].dir.x * rc->ray_dir.x < 0 && rc->side == 0) \
		|| (pl[1].dir.y && pl[1].dir.y * rc->ray_dir.y < 0 && rc->side == 1))
		{
			portal(data, rc, 1, ++deep);
			return ;
		}
	}
}

/**
 * @brief This is the Digital differential analyzer algorithm 
 * that rasterize the ray parcour until it hit a wall or a portal.
 * The (t_int_vector)rc::ipos can be use to know where the DDA stop.
 * 
 * @param data structure with all program data
 * @param rc structure that store all raycast parameters
 * @param deep nb of recursive call made by portal
 */
static void	dda(t_data *data, t_raycast *rc, int deep)
{
	while (1)
	{
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta_dist.x;
			rc->ipos.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			rc->ipos.y += rc->step.y;
			rc->side = 1;
		}
		portal_hit(rc, rc->player.portal, data, deep);
		if (data->map->map[rc->ipos.y][rc->ipos.x] == '1' \
		|| data->map->map[rc->ipos.y][rc->ipos.x] == '2')
		{
			get_tex_ptr(data, rc);
			return ;
		}
	}
}

/**
 * @brief 
 * 
 * @param data structure with all program data
 * @param rc structure that store all raycast parameters
 * @param deep nb of recursive call made by portal
 */
void	cast_a_ray(t_data *data, t_raycast *rc, int deep)
{
	init_ray_param(data->width, rc);
	step_init(rc);
	dda(data, rc, deep);
}
