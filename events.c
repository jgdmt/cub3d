/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:10:19 by jgoudema          #+#    #+#             */
/*   Updated: 2024/03/14 21:12:24 by jgoudema         ###   ########.fr       */
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

void	move(t_data *data, double sp, t_vector v)
{
	int			sign;
	t_vector	pos;
	char		**map;

	sign = 0;
	map = data->map->map;
	pos = data->player->pos;
	if (fabs(v.x) == 1)
		sign = v.x;
	if (map[(int)(pos.y + sign * 0.1)][(int)(pos.x + v.x * sp * 2)] == '0'
		&& map[(int)(pos.y - sign * 0.1)][(int)(pos.x + v.x * sp * 2)] == '0')
		data->player->pos.x += v.x * sp;
	if (fabs(v.y) == 1)
		sign = v.y;
	if (map[(int)(pos.y + v.y * sp * 2)][(int)(pos.x + sign * 0.1)] == '0'
		&& map[(int)(pos.y + v.y * sp * 2)][(int)(pos.x - sign * 0.1)] == '0')
		data->player->pos.y += v.y * sp;
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
		move(data, MSPEED, data->player->dir);
	else if (key.key == MLX_KEY_S)
		move(data, -MSPEED, data->player->dir);
	else if (key.key == MLX_KEY_A)
		move(data, -MSPEED, data->player->plane);
	else if (key.key == MLX_KEY_D)
		move(data, MSPEED, data->player->plane);
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
