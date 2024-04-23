/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bis_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:25:41 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/23 19:34:33 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"
/**
 * @brief Detect a change in width and height from struct data in comparaison
 * with last call a recreate the data->img(mlx_image_t *).
 * If this function encounter a problem they stop the programm with free_all().
 * 
 * @param data structure with all program data
 */
void	resize_render(t_data *data)
{
	int			i;
	mlx_image_t	**cursor;
	bool		check;

	cursor = data->cursor;
	free(data->buff);
	check = mlx_resize_image(data->img, data->width, data->height);
	data->buff = malloc(data->width * data->height * sizeof(int));
	if (!check || !data->buff)
		free_all(ERR_MALLOC, 2, data);
	i = 0;
	while (i < 5)
	{
		cursor[i]->instances[0].x = data->width / 2 - cursor[i]->width / 2;
		cursor[i]->instances[0].y = data->height / 2 - cursor[i]->height / 2;
		i++;
	}
}

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

/**
 * @brief This is the Digital differential analyzer algorithm 
 * that rasterize the ray parcour until it hit a wall or a portal.
 * The (t_int_vector)rc::ipos can be use to know where the DDA stop.
 * 
 * @param data structure with all program data
 * @param rc structure that store all raycast parameters
 */
void	dda(t_data *data, t_raycast *rc, int deep)
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
		if (rc->ipos.y == rc->player.portal[0].pos.y && rc->ipos.x == rc->player.portal[0].pos.x && rc->player.portal[1].status == 1 && deep < 40) // && (rc->player.dir.x * rc->player.portal[0].dir.x) <= 0 && (rc->player.dir.y * rc->player.portal[0].dir.y) <= 0 
		{
			if ((rc->player.portal[0].dir.x && rc->player.portal[0].dir.x * rc->ray_dir.x < 0 && rc->side == 0) || (rc->player.portal[0].dir.y && rc->player.portal[0].dir.y * rc->ray_dir.y < 0 && rc->side == 1))
			{
			portal(data, rc, 0, 1, ++deep);
			return ;
			}
		}
		else if (rc->ipos.y == rc->player.portal[1].pos.y && rc->ipos.x == rc->player.portal[1].pos.x && rc->player.portal[0].status == 1 && deep < 40)
		{
			if ((rc->player.portal[1].dir.x && rc->player.portal[1].dir.x * rc->ray_dir.x < 0 && rc->side == 0) || (rc->player.portal[1].dir.y && rc->player.portal[1].dir.y * rc->ray_dir.y < 0 && rc->side == 1))
			{
			portal(data, rc, 1, 0, ++deep);
			return ;
			}
		}
		 if (data->map->map[rc->ipos.y][rc->ipos.x] == '1' || data->map->map[rc->ipos.y][rc->ipos.x] == '2')
		{
			get_tex_ptr(data, rc);
			return ;
		}
	}
}
