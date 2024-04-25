/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inertia_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:24:32 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/25 17:33:19 by jgoudema         ###   ########.fr       */
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
