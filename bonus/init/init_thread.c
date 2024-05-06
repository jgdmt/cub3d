/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:04:02 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/06 15:13:06 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	init_thread(t_data *data)
{
	pthread_t	thread;
	pthread_t	inertia;
	pthread_t	hud;

	if (pthread_create(&thread, NULL, raycast_threader, data))
		free_all(ERR_MUTEX, 2, data);
	if (pthread_create(&inertia, NULL, update_inertia, data))
		free_all(ERR_MUTEX, 2, data);
	if (pthread_create(&hud, NULL, thread_hud, data))
		free_all(ERR_MUTEX, 2, data);
}
