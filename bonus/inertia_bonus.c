/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inertia_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:24:32 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/25 18:45:26 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Slow the player by tends data::player::vx and data::player::vy towards 0.
 * 
 * @param data structure with all program data
 */
void	*update_inertia(void *gdata)
{
	t_data	*data;
	size_t	last_time;
	size_t	time;

	data = gdata;
	last_time = get_time();
	while (1)
	{
		if (!data->exit)
		{
			// check_death(data);
			move(data);
			data->player->posz += data->player->vz;
			if (data->player->posz > 0)
				data->player->vz -= INERTIA * 100;
			if (data->player->posz == 0)
				data->player->vz = 0;
			if (data->player->vx > 10e-8)
				data->player->vx -= INERTIA;
			else if (data->player->vx < -10e-8)
				data->player->vx += INERTIA;
			if (data->player->vy > 10e-8)
				data->player->vy -= INERTIA;
			else if (data->player->vy < -10e-8)
				data->player->vy += INERTIA;
		}
		time = get_time();
		if (time - last_time < 13)
			ft_usleep(13 - (time - last_time));
		last_time = time;
	}
}
