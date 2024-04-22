/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal_handler_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:27:43 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/22 12:00:47 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <sys/time.h>

/**
 * @brief Set the rc::t pointer to the correct wall texture.
 * It selects the texture from t_data::maps textures in function
 *  of cardinal orientation.
 * 
 * @param data structure with all program data
 * @param rc structure that store all raycast parameters
 */
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

/**
 * @brief Get the time in miliseconds.
 * 
 * @return size_t that represent time in milisecond from 
 */
size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/**
 * @brief Usleep function but with rounded value.
 * 
 * @param msec miliseconds to wait.
 */
void	ft_usleep(size_t msec)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < msec)
		usleep(500);
}

/**
 * @brief Puts RGBA pixel inside t_data::buff for a usage later.
 * 
 * @param data structure with all program data
 * @param x coordonate of the pixel inside the buffer
 * @param y coordonate of the pixel inside the buffer
 * @param color RGBA value store in int for the pixel
 */
void	my_mlx_put_pixel(t_data *data, int x, int y, uint32_t color)
{
	if (y < data->height && x < data->width && x >= 0 && y >= 0)
		data->buff[(y * data->width) + x] = color;
}

/**
 * @brief Copy the whole t_data::buff inside t_data::img for 
 * refresh onscreen image.
 * 
 * @param data structure with all program data
 */
void	put_to_screen(t_data *data)
{
	int			x;
	int			width;
	int			max;
	uint32_t	*buff;

	width = data->width;
	x = 0;
	buff = data->buff;
	max = width * data ->height;
	while (x < max)
	{
		mlx_put_pixel(data->img, x - ((x % width) * width), x % width, buff[x]);
		++x;
	}
}

/**
 * @brief Thread init that calls raycasting 60 times per sec.
 * 
 * @param data structure with all program data
 * @return void* Nothing
 */
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
