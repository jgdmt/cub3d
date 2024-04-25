/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_main_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:22:45 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/25 15:56:47 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief the complete raycast algoritm that generates a frame based 
 * on t_data::map and t_data::player informations.
 * 
 * Can be interrupted by setting data::exit to any positive value.
 * @param data structure with all program data
 */
void	raycast(t_data *data)
{
	t_raycast	rc;
	t_player	temp;

	cursor_screen(data);
	loading_screen(data);
	if (data->exit)
		return ;
	rc.x = 0;
	temp = *(data->player);
	rc.player = temp;
	floor_cast(data, rc.player);
	while (rc.x < data->width)
	{
		rc.player = temp;
		rc.portal_first_ray = 0;
		rc.print = false;
		cast_a_ray(data, &rc, 0);
		if (rc.print == false)
			print_ray(data, &rc);
		rc.x += 1;
	}
	put_to_screen(data);
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