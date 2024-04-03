/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bis_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:25:41 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/03 13:51:34 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	resize_render(t_data *data)
{
	static int	width = WIDTH;
	static int	height = HEIGHT;

	if (width != data->width || height != data->height)
	{
		mlx_delete_image(data->mlx, data->img);
		free(data->buff);
		data->img = mlx_new_image(data->mlx, data->width, data->height);
		data->buff = malloc(data->width * data->height * sizeof(int));
		if (!data->img || !data->buff)
			free_all(ERR_MALLOC, 2, data);
		if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
			free_all(ERR_MLX, 2, data);
		width = data->width;
		height = data->height;
	}
}

void	draw_wall_floor(t_data *data)
{
	u_int32_t	*buff;
	int			size_buff;
	int			i;

	i = 0;
	size_buff = (data->img->width * data->img->height);
	buff = (u_int32_t *)data->img->pixels;
	while (i < size_buff / 2)
	{
		buff[i] = data->map->ceiling_color;
		i++;
	}
	while (i < size_buff)
	{
		buff[i] = data->map->floor_color;
		i++;
	}
}

void	init_ray_param(int width, t_raycast *rc)
{
	double		camera_x;

	camera_x = 2 * rc->x / (double) width - 1;
	rc->ray_dir.x = rc->player.dir.x + rc->player.plane.x * camera_x;
	rc->ray_dir.y = rc->player.dir.y 
		+ rc->player.plane.y * camera_x; 
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

void	dda(t_data *data, t_raycast *rc)
{
	while (1 != 0)
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
		if (data->map->map[rc->ipos.y][rc->ipos.x] == '1')
			return ;
	}
}
