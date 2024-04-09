/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor_sky_casting.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:50:40 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/09 15:42:43 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	get_floor_coord(t_data *data, t_raycast *rc, bool is_floor)
{
	t_vector	ray_dir[2];
	double		row_distance;

	ray_dir[0].x = rc->player.dir.x - rc->player.plane.x;
	ray_dir[0].y = rc->player.dir.y - rc->player.plane.y;
	ray_dir[1].x = rc->player.dir.x + rc->player.plane.x;
	ray_dir[1].y = rc->player.dir.y + rc->player.plane.y;
	if (is_floor)
		row_distance = (0.5 * data->height + rc->player.posz) \
			/ (rc->y - data->height / 2 - rc->player.pitch);
	else
		row_distance = (0.5 * data->height - rc->player.posz) \
			/ (data->height / 2 - rc->y + rc->player.pitch);
	rc->delta_dist.x = row_distance
		* (ray_dir[1].x - ray_dir[0].x) / data->width;
	rc->delta_dist.y = row_distance
		* (ray_dir[1].y - ray_dir[0].y) / data->width;
	rc->ray_dir.x = rc->player.pos.x + row_distance * ray_dir[0].x;
	rc->ray_dir.y = rc->player.pos.y + row_distance * ray_dir[0].y;
}

static void	put_texture(t_data *data, t_raycast *rc, int y, mlx_image_t *tex)
{
	rc->tex.x = (int)(tex->width * (rc->ray_dir.x - rc->ipos.x)) \
		& (tex->width - 1);
	rc->tex.y = (int)(tex->height * (rc->ray_dir.y - rc->ipos.y)) \
		& (tex->height - 1);
	rc->ray_dir.x += rc->delta_dist.x;
	rc->ray_dir.y += rc->delta_dist.y;
	my_mlx_put_pixel(data, rc->x, y, correct_color(\
		&(tex->pixels[((tex->width * rc->tex.y) + rc->tex.x) * 4])));
}

void	floor_cast(t_data *data, t_player player)
{
	t_raycast	rc;
	bool		is_floor;

	rc.player = player;
	rc.y = 0;
	while (rc.y < data->height)
	{
		is_floor = rc.y > data->height / 2 + rc.player.pitch;
		get_floor_coord(data, &rc, is_floor);
		rc.x = 0;
		while (rc.x < data->width)
		{
			rc.ipos.x = (int)(rc.ray_dir.x);
			rc.ipos.y = (int)(rc.ray_dir.y);
			if (is_floor)
				put_texture(data, &rc, rc.y, data->map->floor_color);
			else
				put_texture(data, &rc, rc.y, data->map->ceiling_color);
			rc.x++;
		}
		rc.y++;
	}
}
