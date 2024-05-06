/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_minimap_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:51:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/06 14:31:40 by vilibert         ###   ########.fr       */
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

static void	fill_map(t_data *data, t_vector *pos, t_vector delt, t_int_vector i)
{
	t_portal	*pl;

	pl = data->player->portal;
	if (pos->x < 0 || pos->y < 0 || !data->map->map[(int)floor(pos->y)] \
	[(int)floor(pos->x)])
		data->hud.buff[(data->hud.img->width * i.x) + i.y] = 0xff898989;
	else if (data->map->map[(int)floor(pos->y)][(int)floor(pos->x)] == '1')
		data->hud.buff[(data->hud.img->width * i.x) + i.y] = 0xff898989;
	else if (data->map->map[(int)floor(pos->y)][(int)floor(pos->x)] == '0')
		data->hud.buff[(data->hud.img->width * i.x) + i.y] = 0xffbbdbf5;
	else
		data->hud.buff[(data->hud.img->width * i.x) + i.y] = 0xff898989;
	if (pl[0].status == 1 && pl[0].pos.x == floor(pos->x) && pl[0].pos.y \
	== floor(pos->y))
		data->hud.buff[(data->hud.img->width * i.x) + i.y] = 0xfffcdc04;
	else if (pl[1].status == 1 && pl[1].pos.x == floor(pos->x) && pl[1].pos.y \
	== floor(pos->y))
		data->hud.buff[(data->hud.img->width * i.x) + i.y] = 0xff049cfc;
	if (is_enemy(data, pos->x, pos->y, -1) != -1)
		data->hud.buff[(data->hud.img->width * i.x) + i.y] = 0xff000000;
	if ((pos->x > 0 && pos->y > 0 && data->map->map[(int)floor(pos->y)] \
	[(int)floor(pos->x)]) || pos->x < 0)
		pos->x += delt.x;
}

void	get_minimap(t_data *data)
{
	t_vector		pos;
	t_vector		temp_pos;
	t_vector		delta;
	t_int_vector	i;

	delta.x = (double)10 / data->hud.img->width;
	delta.y = (double)10 / (data->hud.img->height - 15);
	temp_pos = data->player->pos;
	pos = temp_pos;
	pos.y -= 5;
	i.x = 0;
	while ((unsigned int)i.x < data->hud.img->height - 15)
	{
		i.y = data->hud.img->width;
		pos.x = temp_pos.x - 5;
		while (--i.y >= 0)
			fill_map(data, &pos, delta, i);
		if ((pos.x > 0 && pos.y > 0 && \
		data->map->map[(int)ceil(pos.y)]) || pos.y < 0)
			pos.y += delta.y;
		i.x++;
	}
	put_buff(data->hud.img, data->hud.buff, data);
}
