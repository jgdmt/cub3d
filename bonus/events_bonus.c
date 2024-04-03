/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:10:19 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/03 17:44:31 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	// raycast(data);
}

void	move(t_data *data, double sp, t_vector v)
{
	int			sign;
	t_vector	pos;
	char		**map;

	// pthread_mutex_lock(&(data->lock));
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
	// pthread_mutex_unlock(&(data->lock));
	// raycast(data);
}


void	mouse_move(void *gdata)
{
	static int32_t	old_x = WIDTH / 2;
	static int32_t	old_y = HEIGHT / 2;
	int32_t			x;
	int32_t			y;
	t_data			*data;

	data = gdata;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (data->exit)
	{
		old_x = x;
		old_y = y;
		return ;
	}
	if (x < old_x)
		rotate(RSPEED, data);
	else if (x > old_x)
		rotate(-RSPEED, data);
	old_x = x;
	old_y = y;
}

void	hook(void *gdata)
{
	t_data 		*data;
	static int	i = 0;
	static size_t	last_time = 0;

	data = gdata;
	if (i < 2)
	{
		last_time = get_time();
		mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
		i++;
	}
	if (13 > get_time() - last_time)
		return ;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		menu(data);
	if (data->exit)
		return ;
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		free_all("Game quit", 1, data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate(RSPEED, data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate(-RSPEED, data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move(data, MSPEED, data->player->dir);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move(data, -MSPEED, data->player->dir);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move(data, -MSPEED, data->player->plane);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move(data, MSPEED, data->player->plane);
	if (mlx_is_key_down(data->mlx, MLX_KEY_N))
		change_map(data);
	mouse_move(gdata);
	last_time = get_time();
	// raycast(data);
}

void	close_window(void *gdata)
{
	t_data	*data;

	data = gdata;
	free_all("Game closed", 1, data);
}

void	resize_window(int32_t width, int32_t height, void *gdata)
{
	t_data	*data;

	data = gdata;
	data->width = width;
	data->height = height;
	resize_render(data);
}
