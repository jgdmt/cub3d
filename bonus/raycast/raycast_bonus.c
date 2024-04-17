/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:12:11 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/16 16:51:26 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	correct_color(u_int8_t *pixel)
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

	y = 0;
	step = 1.0 * rc->t->height / rc->line_height;
	tex_pos = (rc->draw_start - rc->player.pitch - data->height / 2 + rc->line_height / 2) * step;
	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		rc->tex.y = (int)tex_pos & (rc->t->height - 1);
		tex_pos += step;
		color = correct_color((u_int8_t *)&((u_int32_t *)rc->t->pixels)
			[rc->t->width * rc->tex.y + (rc->t->width - rc->tex.x - 1)]);
		my_mlx_put_pixel(data, rc->x, y, color);
		y++;
	}
}

static void	get_screen_coord(t_data *data, t_raycast *rc)
{
	rc->line_height = (int)(data->height / rc->perp_wall_dist);
	rc->draw_start = (-rc->line_height / 2 + data->height / 2) + rc->player.pitch;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = (rc->line_height / 2 + data->height / 2) + rc->player.pitch;
	if (rc->draw_end >= data->height)
		rc->draw_end = data->height - 1;
}

static void	get_tex_coord(t_raycast *rc)
{
	double	wall_x;

	if (rc->side == 0)
		wall_x = rc->player.pos.y + (rc->perp_wall_dist - rc->portal_first_ray)* rc->ray_dir.y;
	else
		wall_x = rc->player.pos.x + (rc->perp_wall_dist - rc->portal_first_ray) * rc->ray_dir.x;
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
	t_player	temp;

	cursor_screen(data);
	loading_screen(data);
	if (data->exit)
		return ;
	rc.x = 0;
	temp = *(data->player);
	rc.player = temp;
	floor_cast(data, rc.player);
	while (rc.x < data->width)
	{
		rc.player = temp;
		rc.portal_first_ray = 0;
		init_ray_param(data->width, &rc);
		step_init(&rc);
		dda(data, &rc);
		if (rc.side == 0)
			rc.perp_wall_dist = (rc.side_dist.x - rc.delta_dist.x) + rc.portal_first_ray;
		else
			rc.perp_wall_dist = (rc.side_dist.y - rc.delta_dist.y) + rc.portal_first_ray;
		get_screen_coord(data, &rc);
		get_tex_coord(&rc);
		ray_to_img(data, &rc);
		rc.x += 1;
	}
	put_to_screen(data);
}
