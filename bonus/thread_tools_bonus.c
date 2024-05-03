/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_tools_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:01:36 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/03 20:40:11 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <sys/time.h>

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

void	*atk_sprite(void *genemy)
{
	t_enemy	*enemy;

	enemy = genemy;
	enemy->flag = 1;
	enemy->t = enemy->en_sprites[3];
	ft_usleep(250);
	enemy->t = enemy->en_sprites[0];
	enemy->flag = 0;
	return (NULL);
}
