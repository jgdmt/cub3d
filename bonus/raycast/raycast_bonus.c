/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:12:11 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/25 18:51:07 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief Gets the screen start and end of a wall column.
 * 
 * @param data structure with all program data
 * @param rc structure that store all raycast parameters
 */
static void	get_screen_coord(t_data *data, t_raycast *rc)
{
	rc->line_height = (int)(data->height / rc->perp_wall_dist);
	rc->draw_start = (-rc->line_height / 2 + data->height / 2) \
	+ rc->player.pitch + ((double)rc->player.posz / rc->perp_wall_dist);
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = (rc->line_height / 2 + data->height / 2) + rc->player.pitch + (double)((double)rc->player.posz / rc->perp_wall_dist);
	if (rc->draw_end >= data->height)
		rc->draw_end = data->height - 1;
}

/**
 * @brief Gets the texture image start and end for a wall column.
 * 
 * @param rc structure that store all raycast parameters
 */
static void	get_tex_coord(t_raycast *rc)
{
	double	wall_x;
	double	perp_wall_dist_corr;

	perp_wall_dist_corr = rc->perp_wall_dist - rc->portal_first_ray;
	if (rc->side == 0)
		wall_x = rc->player.pos.y + perp_wall_dist_corr * rc->ray_dir.y;
	else
		wall_x = rc->player.pos.x + perp_wall_dist_corr * rc->ray_dir.x;
	wall_x -= floor((wall_x));
	rc->tex.x = (int)(wall_x * (double)(rc->t->width));
	if (rc->side == 0 && rc->ray_dir.x > 0)
		rc->tex.x = rc->t->width - rc->tex.x - 1;
	if (rc->side == 1 && rc->ray_dir.y < 0)
		rc->tex.x = rc->t->width - rc->tex.x - 1;
}

/**
 * @brief Needs to be called at the end of raycasting.
 *  The x wall's column is put inside the t_data::buff.
 * 
 * @param data structure with all program data
 * @param rc structure that store all raycast parameters
 */
static void	ray_to_img(t_data *data, t_raycast *rc)
{
	double		step;
	double		tex_pos;
	u_int32_t	color;
	int			y;

	y = 0;
	step = 1.0 * rc->t->height / rc->line_height;
	tex_pos = (rc->draw_start - rc->player.pitch - (data->player->posz / rc->perp_wall_dist) - data->height / 2 \
	+ rc->line_height / 2) * step;
	y = rc->draw_start;
	while (y <= rc->draw_end)
	{
		rc->tex.y = (int)tex_pos & (rc->t->height - 1);
		tex_pos += step;
		color = correct_color((u_int8_t *)&((u_int32_t *)rc->t->pixels)
			[rc->t->width * rc->tex.y + (rc->t->width - rc->tex.x - 1)]);
		my_mlx_put_pixel(data, rc->x, y, color);
		y++;
	}
}

void	print_ray(t_data *data, t_raycast *rc)
{
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->side_dist.x - rc->delta_dist.x);
	else
		rc->perp_wall_dist = (rc->side_dist.y - rc->delta_dist.y);
	rc->perp_wall_dist += rc->portal_first_ray;
	get_screen_coord(data, rc);
	get_tex_coord(rc);
	ray_to_img(data, rc);
}
