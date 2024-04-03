/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:10:19 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/03 22:36:45 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	tp(t_data *data, int to)
{
	int	sign;

	data->exit = 2;
	ft_usleep(250);
	data->player->pos.x = data->player->portal[to].pos.x + data->player->portal[to].dir.x;
	data->player->pos.y = data->player->portal[to].pos.y + data->player->portal[to].dir.y;
	data->player->dir.x = data->player->portal[to].dir.x;
	data->player->dir.y = data->player->portal[to].dir.y;
	sign = -1;
	if (data->player->portal[to].dir.x == 0)
		sign = 1;
	data->player->plane.x = sign * data->player->portal[to].dir.y;
	data->player->plane.y = sign * data->player->portal[to].dir.x;
	data->exit = 0;
}

int	check_portal(t_data *data, int x, int y)
{
	t_portal	*port;
	int			i;

	port = data->player->portal;
	i = 0;
	printf("Going to %i %i\n", x, y);
	while (i < 2)
	{
		if (port[i].status && ((port[i].pos.y == y && (port[i].pos.x == x + 1
						|| port[i].pos.x == x - 1)) || (port[i].pos.x == x
					&& (port[i].pos.y == y + 1 || port[i].pos.y == y - 1))))
		{
			if (i == BLUE && port[ORANGE].status)
				return (tp(data, ORANGE), 1);
			if (i == ORANGE && port[BLUE].status)
				return (tp(data, BLUE), 1);
		}
		i++;
	}
	return (0);
}

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

	sign = 0;
	map = data->map->map;
	pos = data->player->pos;
	if (fabs(v.x) == 1)
		sign = v.x;
	if (map[(int)(pos.y + sign * 0.1)][(int)(pos.x + v.x * sp * 2)] == '0'
		&& map[(int)(pos.y - sign * 0.1)][(int)(pos.x + v.x * sp * 2)] == '0')
		data->player->pos.x += v.x * sp;
	else
		if (check_portal(data, pos.x + v.x * sp, data->player->pos.y))
			return ;
	if (fabs(v.y) == 1)
		sign = v.y;
	if (map[(int)(pos.y + v.y * sp * 2)][(int)(pos.x + sign * 0.1)] == '0'
		&& map[(int)(pos.y + v.y * sp * 2)][(int)(pos.x - sign * 0.1)] == '0')
		data->player->pos.y += v.y * sp;
	else
		if (check_portal(data, pos.x, data->player->pos.y + v.y * sp))
			return ;
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
	if(y < old_y && data->player->pitch < 500)
		data->player->pitch += 40;
	if(y > old_y && data->player->pitch > -500)
		data->player->pitch -= 40;
	old_x = x;
	old_y = y;
}

void	hook(void *gdata)
{
	t_data			*data;
	static int		i = 0;
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
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q) && data->exit == 1)
		free_all("Game quit", 1, data);
	if (data->exit)
		return ;
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
