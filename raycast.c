/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:12:11 by vilibert          #+#    #+#             */
/*   Updated: 2024/03/14 17:19:28 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resize_render(t_data *data);
void	draw_wall_floor(t_data *data);
void	init_ray_param(t_data *data, t_raycast *rc);
void	step_init(t_data *data, t_raycast *rc);
void	dda(t_data *data, t_raycast *rc);

// # include <sys/time.h>

// size_t	get_current_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		write(2, "gettimeofday() error\n", 22);
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

static int	correct_color(u_int8_t *pixel)
{
	int	rgba;

	rgba = 0;
	rgba += pixel[0] << 24;
	rgba += pixel[1] << 16;
	rgba += pixel[2] << 8;
	rgba += pixel[3];
	return (rgba);
}

static void	ray_to_img(t_data *data, t_raycast *rc)
{
	double	step;
	double	tex_pos;
	int		y;

	step = 1.0 * data->map->no->height / rc->line_height;
	tex_pos = (rc->draw_start - data->height / 2 + rc->line_height / 2) * step;
	y = rc->draw_start;
	while (y <= rc->draw_end)
	{
		rc->tex.y = (int)tex_pos & (data->map->no->height - 1);
		tex_pos += step;
		u_int32_t color = correct_color((u_int8_t*)&((u_int32_t*)data->map->no->pixels)[data->map->no->width * rc->tex.y + (data->map->no->width - rc->tex.x - 1)]);
		if (rc->side == 1)
			color = (color >> 1) & 8355711;
		mlx_put_pixel(data->img, rc->x, y, color);
		y++;
	}
}

static void	get_screen_coord(t_data *data, t_raycast *rc)
{
	rc->line_height = (int)(data->height / rc->perpWallDist);
	rc->draw_start = -rc->line_height / 2 + data->height / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + data->height / 2;
	if (rc->draw_end >= data->height)
		rc->draw_end = data->height - 1;
}

static void	get_tex_coord(t_data *data, t_raycast *rc)
{
	double	wall_x;

	if (rc->side == 0)
		wall_x = data->player->pos.y + rc->perpWallDist * rc->ray_dir.y;
	else
		wall_x = data->player->pos.x + rc->perpWallDist * rc->ray_dir.x;
	wall_x -= floor((wall_x));
	rc->tex.x = (int)(wall_x * (double)(data->map->no->width));
	if (rc->side == 0 && rc->ray_dir.x > 0)
		rc->tex.x = data->map->no->width - rc->tex.x - 1;
	if (rc->side == 1 && rc->ray_dir.y < 0)
		rc->tex.x = data->map->no->width - rc->tex.x - 1;
}

void	raycast(t_data *data)
{
	t_raycast	rc;

	resize_render(data);
	draw_wall_floor(data);
	rc.x = 0;
	while (rc.x < data->width)
	{
		init_ray_param(data, &rc);
		step_init(data, &rc);
		dda(data, &rc);
		get_screen_coord(data, &rc);
		if (rc.side == 0)
			rc.perpWallDist = (rc.side_dist.x - rc.delta_dist.x);
		else
			rc.perpWallDist = (rc.side_dist.y - rc.delta_dist.y);
		get_tex_coord(data, &rc);
		ray_to_img(data, &rc);
		(rc.x)++;
	}
}
