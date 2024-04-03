/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal_handler_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:27:43 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/03 13:42:27 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <sys/time.h>

void	get_tex_ptr(t_data *data, t_raycast *rc)
{
	if (rc->ipos.x >= rc->player.pos.x && rc->side == 0)
	{
		rc->t = data->map->ea;
	}
	if (rc->ipos.x < rc->player.pos.x && rc->side == 0)
	{
		rc->t = data->map->we;
	}
	if (rc->ipos.y >= rc->player.pos.y && rc->side == 1)
	{
		rc->t = data->map->no;
	}
	if (rc->ipos.y < rc->player.pos.y && rc->side == 1)
	{
		rc->t = data->map->so;
	}
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t msec)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < msec)
		usleep(500);
}

void	my_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	int	*buff;

	buff = (int *)data->buff;
	if (y < data->height && x < data->width)
		buff[(y * data->width) + x] = color;
}

void	put_to_screen(t_data *data)
{
	int	x;
	int	width;
	int	*buff;

	buff = (int *)data->buff;
	width = data->width;
	x = 0;
	while (x < width * data->height)
	{
		mlx_put_pixel(data->img, x - ((x % width) * width), x % width, buff[x]);
		++x;
	}
}

void	*raycast_threader(void *data)
{
	size_t	last_time;
	size_t	time;

	last_time = get_time();

	while (1)
	{
		raycast((t_data *)data);
		time = get_time();
		if (time - last_time < 13)
			ft_usleep(13 - (time - last_time));
		last_time = time;
	}
}
