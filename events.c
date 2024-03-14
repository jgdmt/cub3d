/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:10:19 by jgoudema          #+#    #+#             */
/*   Updated: 2024/03/14 16:23:58 by jgoudema         ###   ########.fr       */
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

void	move_forward(t_data *data, double speed)
{
	int			sign;
	int			x;
	int			y;

	sign = 0;
	if (fabs(data->player->dir.x) == 1)
		sign = data->player->dir.x; 
	x = (int)(data->player->pos.x + data->player->dir.x * speed * 2);
	y = (int)(data->player->pos.y + sign * 0.1);
	if (data->map->map[y][x] == '0')
		data->player->pos.x += data->player->dir.x * speed;
	if (fabs(data->player->dir.y) == 1)
		sign = data->player->dir.y;
	x = (int)(data->player->pos.x + sign * 0.1);
	y = (int)(data->player->pos.y + data->player->dir.y * speed * 2);
	if (data->map->map[y][x] == '0')
		data->player->pos.y += data->player->dir.y * speed;
	raycast(data);
}

void	move(t_data *data, double speed)
{
	int			sign;
	int			x;
	int			y;

	sign = 0;
	if (fabs(data->player->plane.x) == 1)
		sign = data->player->plane.x;
	x = (int)(data->player->pos.x + data->player->plane.x * speed * 2);
	y = (int)(data->player->pos.y + 0.1 * sign);
	if (data->map->map[y][x] == '0')
		data->player->pos.x += data->player->plane.x * speed;
	if (fabs(data->player->plane.y) == 1)
		sign = data->player->plane.y;
	x = (int)(data->player->pos.x + sign * 0.1);
	y = (int)(data->player->pos.y + data->player->plane.y * speed * 2);
	if (data->map->map[y][x] == '0')
		data->player->pos.y += (data->player->plane.y) * speed;
	raycast(data);
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
		move_forward(data, MSPEED);
	else if (key.key == MLX_KEY_S)
		move_forward(data, -MSPEED);
	else if (key.key == MLX_KEY_A)
		move(data, -MSPEED);
	else if (key.key == MLX_KEY_D)
		move(data, MSPEED);
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
