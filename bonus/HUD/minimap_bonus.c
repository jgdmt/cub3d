/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:51:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/02 17:45:35 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	put_rot_px(t_int_vector coord, uint32_t color, float theta, t_data *data)
{
	t_int_vector	coord_rot;
	int	mid_x = data->hud.width / 2;
	int	mid_y = (data->hud.height - 15) / 2;
	coord_rot.x = (coord.x - mid_x) * cos(theta) + (coord.y - mid_y) * -sin(theta);
	coord_rot.y = (coord.x - mid_x) * sin(theta) + (coord.y - mid_y) * cos(theta);
	if (coord_rot.x + mid_x <  0 || coord_rot.y + mid_y < 0 || coord_rot.x + mid_x >= data->hud.width || coord_rot.y + mid_y >= data->hud.height - 15)
		return;
	((uint32_t *)data->hud.img->pixels)[((coord_rot.y + mid_y) * data->hud.width) + (coord_rot.x + mid_x)] = color;
	// ((uint32_t *)data->hud.img->pixels)[(coord.y * data->hud.img->width) + coord.x] = color;
}

static void	put_buff(mlx_image_t *hud, uint32_t *buff, t_data *data)
{
	t_int_vector	i;
	t_vector		dist;
	double			distance;
	float			theta;

	i.y = 0;
	theta = angle(data->player->dir.x, data->player->dir.y, 0, -1);
	while ((u_int32_t)i.y < hud->height - 15)
	{
		i.x = 0;
		while ((u_int32_t)i.x < hud->width)
		{
			dist.x = pow((double)i.x - ((double)hud->width / 2), 2);
			dist.y = pow((double)i.y - ((double)(hud->height - 15) / 2), 2);
			distance = sqrt(dist.x + dist.y) - (double)hud->width / 2;
			if (distance <= 0.00000000)
			{
				if (distance <= -1.00000000)
					put_rot_px(i, buff[(i.y * hud->width) + i.x], theta, data);
				else
					// data->hud.img->pixels[(i.y * data->hud.img->width) + i.x] =  0xff000000;
					put_rot_px(i, 0xff000000, theta, data);
			}
			(i.x)++;
		}
		(i.y)++;
	}
}

int	is_enemy2(t_data *data, double i, double j)
{
	int	k;

	k = 0;
	while (k < data->map->nb_enemy)
	{
		if (data->map->enemies[k].status && fabs(data->map->enemies[k].pos.x - i) < 0.5f && fabs(data->map->enemies[k].pos.y - j) < 0.5f)
			return (1);
		k++;
	}
	return (0);
}

void	get_minimap(t_data *data)
{
	t_vector	pos;
	t_vector	temp_pos;
	t_vector	delta;
	int			i;
	int			j;

	delta.x = (double)10 / data->hud.width;
	delta.y = (double)10 / (data->hud.height - 15);
	temp_pos = data->player->pos;
	pos = temp_pos;
	pos.y -= 5;
	i = 0;
	while (i < data->hud.height - 15)
	{
		j = data->hud.width - 1;
		pos.x = temp_pos.x - 5;
		while (j >= 0)
		{
			if (pos.x < 0 || pos.y < 0 || !data->map->map[(int)floor(pos.y)][(int)floor(pos.x)])
				data->hud.buff[(data->hud.width * i) + j] = 0xff898989;
			else if (data->map->map[(int)floor(pos.y)][(int)floor(pos.x)] == '1')
				data->hud.buff[(data->hud.width * i) + j] = 0xff898989;
			else if (data->map->map[(int)floor(pos.y)][(int)floor(pos.x)] == '0')
				data->hud.buff[(data->hud.width * i) + j] = 0xffbbdbf5;
			else
				data->hud.buff[(data->hud.width * i) + j] = 0xff898989;
			if (data->player->portal[0].status == 1 && data->player->portal[0].pos.x == floor(pos.x) && data->player->portal[0].pos.y == floor(pos.y))
				data->hud.buff[(data->hud.width * i) + j] = 0xfffcdc04;
			else if (data->player->portal[1].status == 1 && data->player->portal[1].pos.x == floor(pos.x) && data->player->portal[1].pos.y == floor(pos.y))
				data->hud.buff[(data->hud.width * i) + j] = 0xff049cfc;
			if (is_enemy2(data, pos.x, pos.y))
				data->hud.buff[(data->hud.width * i) + j] = 0xff000000;
			
			if ((pos.x > 0 && pos.y > 0 && data->map->map[(int)floor(pos.y)][(int)floor(pos.x)]) || pos.x < 0)
				pos.x += delta.x;
			j--;
		}
		if ((pos.x > 0 && pos.y > 0 && data->map->map[(int)ceil(pos.y)]) || pos.y < 0)
			pos.y += delta.y;
		i++;
	}
	put_buff(data->hud.img, data->hud.buff, data);
	mlx_put_pixel(data->hud.img, data->hud.img->width / 2, (data->hud.img->height - 15) / 2, 0xff0000ff);
}
