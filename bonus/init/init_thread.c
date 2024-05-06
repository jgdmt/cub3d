/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:04:02 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/06 17:48:51 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	init_thread(t_data *data)
{
	if (pthread_create(&data->threads[0], NULL, raycast_threader, data))
		free_all(ERR_MUTEX, 2, data);
	if (pthread_create(&data->threads[1], NULL, update_inertia, data))
		free_all(ERR_MUTEX, 2, data);
	if (pthread_create(&data->threads[2], NULL, thread_hud, data))
		free_all(ERR_MUTEX, 2, data);
}
