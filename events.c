/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:10:19 by jgoudema          #+#    #+#             */
/*   Updated: 2024/03/13 19:16:19 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(double speed, t_data *data)
{
	double	old_x;
	double	old_y;

	old_x = data->player->dir.x;
	old_y = data->player->dir.y;
	data->player->dir.x = old_x * cos(speed) - old_y * sin(speed);
	data->player->dir.y = old_x * sin(speed) + old_y * cos(speed);
	old_x = data->player->plane.x;
	old_y = data->player->plane.y;
	data->player->plane.x = old_x * cos(speed) - old_y * sin(speed);
	data->player->plane.y = old_x * sin(speed) + old_y * cos(speed);
	raycast(data);
}

void	move_forward(t_data *data, double xspeed, double yspeed)
{
	data->player->pos.x += data->player->dir.x * xspeed;
	data->player->pos.y += data->player->dir.y * yspeed;

}

void	keypress(mlx_key_data_t key, void *gdata)
{
	t_data	*data;

	data = gdata;
	if (key.key == MLX_KEY_ESCAPE)
		free_all("Game escaped\n", 1, data);
	else if (key.key == MLX_KEY_LEFT)
		rotate(RSPEED, data);
	else if (key.key == MLX_KEY_RIGHT)
		rotate(-RSPEED, data);
	else if (key.key == MLX_KEY_W)
		move_forward(data, MSPEED, MSPEED);
	// else if (key.key == S)
	// 	move();
	// else if (key.key == A)
	// 	move();
	// else if (key.key == D)
	// 	move();
}

void	close_window(void *gdata)
{
	t_data	*data;

	data = gdata;
	free_all("Game closed\n", 1, data);
}

void	resize_window(int32_t width, int32_t height, void *gdata)
{
	t_data	*data;

	data = gdata;
	data->width = width;
	data->height = height;
	raycast(data);
}
