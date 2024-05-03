/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_minimap_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:51:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/03 20:42:20 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	put_rot_px(t_int_vector coord, uint32_t color, float th, t_data *data)
{
	t_int_vector	rot;
	t_int_vector	mid;
	t_int_vector	img;
	uint32_t		*px;

	img.x = data->hud.img->width;
	img.y = data->hud.img->height;
	px = (uint32_t *)data->hud.img->pixels;
	mid.x = img.x / 2;
	mid.y = (img.y - 15) / 2;
	rot.x = (coord.x - mid.x) * cos(th) + (coord.y - mid.y) * -sin(th);
	rot.y = (coord.x - mid.x) * sin(th) + (coord.y - mid.y) * cos(th);
	if (rot.x + mid.x < 0 || rot.y + mid.y < 0 || rot.x + mid.x >= img.x \
	|| rot.y + mid.y >= img.y - 15)
		return ;
	if (px[((rot.y + mid.y) * img.x) + (rot.x + mid.x)] == 0xff0000ff)
		return ;
	px[((rot.y + mid.y) * img.x) + (rot.x + mid.x)] = color;
}

static void	put_buff(mlx_image_t *hud, uint32_t *buff, t_data *data)
{
	t_int_vector	i;
	t_vector		dist;
	double			distance;
	float			theta;

	i.y = -1;
	theta = angle(data->player->dir.x, data->player->dir.y, 0, -1);
	while ((u_int32_t)++i.y < hud->height - 15)
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
					put_rot_px(i, 0xff000000, theta, data);
			}
			(i.x)++;
		}
	}
}

int	is_enemy2(t_data *data, double i, double j)
{
	int	k;

	k = 0;
	while (k < data->map->nb_enemy)
	{
		if (data->map->enemies[k].status && \
		fabs(data->map->enemies[k].pos.x - i) < 0.5f \
		&& fabs(data->map->enemies[k].pos.y - j) < 0.5f)
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
	uint32_t	i;
	int			j;

	delta.x = (double)10 / data->hud.img->width;
	delta.y = (double)10 / (data->hud.img->height - 15);
	temp_pos = data->player->pos;
	pos = temp_pos;
	pos.y -= 5;
	i = 0;
	while (i < data->hud.img->height - 15)
	{
		j = data->hud.img->width - 1;
		pos.x = temp_pos.x - 5;
		while (j >= 0)
		{
			if (pos.x < 0 || pos.y < 0 || !data->map->map[(int)floor(pos.y)][(int)floor(pos.x)])
				data->hud.buff[(data->hud.img->width * i) + j] = 0xff898989;
			else if (data->map->map[(int)floor(pos.y)][(int)floor(pos.x)] == '1')
				data->hud.buff[(data->hud.img->width * i) + j] = 0xff898989;
			else if (data->map->map[(int)floor(pos.y)][(int)floor(pos.x)] == '0')
				data->hud.buff[(data->hud.img->width * i) + j] = 0xffbbdbf5;
			else
				data->hud.buff[(data->hud.img->width * i) + j] = 0xff898989;
			if (data->player->portal[0].status == 1 && data->player->portal[0].pos.x == floor(pos.x) && data->player->portal[0].pos.y == floor(pos.y))
				data->hud.buff[(data->hud.img->width * i) + j] = 0xfffcdc04;
			else if (data->player->portal[1].status == 1 && data->player->portal[1].pos.x == floor(pos.x) && data->player->portal[1].pos.y == floor(pos.y))
				data->hud.buff[(data->hud.img->width * i) + j] = 0xff049cfc;
			if (is_enemy2(data, pos.x, pos.y))
				data->hud.buff[(data->hud.img->width * i) + j] = 0xff000000;
			
			if ((pos.x > 0 && pos.y > 0 && data->map->map[(int)floor(pos.y)][(int)floor(pos.x)]) || pos.x < 0)
				pos.x += delta.x;
			j--;
		}
		if ((pos.x > 0 && pos.y > 0 && data->map->map[(int)ceil(pos.y)]) || pos.y < 0)
			pos.y += delta.y;
		i++;
	}
	put_buff(data->hud.img, data->hud.buff, data);
}
