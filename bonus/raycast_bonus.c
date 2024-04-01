/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:12:11 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/01 18:33:02 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	resize_render(t_data *data);
void	draw_wall_floor(t_data *data);
void	init_ray_param(t_data *data, t_raycast *rc);
void	step_init(t_data *data, t_raycast *rc);
void	dda(t_data *data, t_raycast *rc);
void	get_tex_ptr(t_data *data, t_raycast *rc);

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
	double		step;
	double		tex_pos;
	u_int32_t	color;
	int			y;

	y= 0;
	step = 1.0 * data->map->no->height / rc->line_height;
	tex_pos = (rc->draw_start - data->height / 2 + rc->line_height / 2) * step;
	while (y <= rc->draw_start)
		my_mlx_put_pixel(data, rc->x, y++, data->map->ceiling_color);
	while (y <= rc->draw_end)
	{
		rc->tex.y = (int)tex_pos & (data->map->no->height - 1);
		tex_pos += step;
		color = correct_color((u_int8_t *)&((u_int32_t *)rc->t->pixels)
			[rc->t->width * rc->tex.y + (rc->t->width - rc->tex.x - 1)]);
		my_mlx_put_pixel(data, rc->x, y, color);
		y++;
	}
	while (y <= data->height)
		my_mlx_put_pixel(data, rc->x, y++, data->map->floor_color);
}

static void	get_screen_coord(t_data *data, t_raycast *rc)
{
	rc->line_height = (int)(data->height / rc->perp_wall_dist);
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
		wall_x = data->player->pos.y + rc->perp_wall_dist * rc->ray_dir.y;
	else
		wall_x = data->player->pos.x + rc->perp_wall_dist * rc->ray_dir.x;
	wall_x -= floor((wall_x));
	rc->tex.x = (int)(wall_x * (double)(rc->t->width));
	if (rc->side == 0 && rc->ray_dir.x > 0)
		rc->tex.x = rc->t->width - rc->tex.x - 1;
	if (rc->side == 1 && rc->ray_dir.y < 0)
		rc->tex.x = rc->t->width - rc->tex.x - 1;
}

void	raycast(t_data *data)
{
	t_raycast	rc;

	pthread_mutex_lock(&(data->lock));
	if (data->exit)
		return ;
	resize_render(data);
	rc.x = 0;
	while (rc.x < data->width)
	{
		init_ray_param(data, &rc);
		step_init(data, &rc);
		dda(data, &rc);
		if (rc.side == 0)
			rc.perp_wall_dist = (rc.side_dist.x - rc.delta_dist.x);
		else
			rc.perp_wall_dist = (rc.side_dist.y - rc.delta_dist.y);
		get_screen_coord(data, &rc);
		get_tex_ptr(data, &rc);
		get_tex_coord(data, &rc);
		ray_to_img(data, &rc);
		rc.x += 1;
	}
	put_to_screen(data);
	pthread_mutex_unlock(&(data->lock));
}
