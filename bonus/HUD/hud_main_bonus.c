/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_main_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:32:23 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/06 16:15:20 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	*thread_hud(void *gdata)
{
	t_data	*data;
	size_t	last_time;
	size_t	time;

	data = gdata;
	last_time = get_time();
	while (data->exit != EXIT)
	{
		if (!data->exit)
		{
			print_hp(data);
			get_minimap(data);
		}
		time = get_time();
		if (time - last_time < 13)
			ft_usleep(13 - (time - last_time));
		last_time = time;
	}
	return (NULL);
}
