/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal_handler_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:27:43 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/01 15:02:53 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <sys/time.h>

void	get_tex_ptr(t_data *data, t_raycast *rc)
{
	if (rc->ipos.x >= data->player->pos.x && rc->side == 0)
	{
		rc->t = data->map->ea;
	}
	if (rc->ipos.x < data->player->pos.x && rc->side == 0)
	{
		rc->t = data->map->we;
	}
	if (rc->ipos.y >= data->player->pos.y && rc->side == 1)
	{
		rc->t = data->map->no;
	}
	if (rc->ipos.y < data->player->pos.y && rc->side == 1)
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

void	*raycast_threader(void *data)
{
	size_t	last_time;
	size_t	time;

	last_time = get_time();
	// printf("%zu\n", get_time());
	// ft_usleep(30);
	// printf("%zu\n", get_time());
	while (1)
	{
		raycast((t_data *)data);
		time = get_time();
		if (time - last_time < 16)
			ft_usleep(16 - (time - last_time));
		last_time = time;
	}
}
