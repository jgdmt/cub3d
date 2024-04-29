/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_gun_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:36:49 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/29 16:55:11 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	get_ray(t_data *data, t_raycast *rc);

/**
 * @brief Unfinished function.
 * 
 * @param map 
 * @param rc 
 * @return int 
 */
int	is_enemy(t_map *map, t_raycast *rc)
{
	int	i;

	i = 0;
	while (i < map->nb_enemy)
	{
		if (map->enemies[i].status && map->enemies[i].pos.x == rc->ipos.x
			&& map->enemies[i].pos.y == rc->ipos.y)
			return (i);
		i++;
	}
	return (-1);
}

void	*gun_shot(void *gdata)
{
	t_data	*data;
	// int		i;

	data = gdata;
	// i = 0;
	// while (i < 4)
	// {
	// 	data->gun[i]->enabled = false;
	// 	data->gun[i + 1]->enabled = true;
	// 	i++;
	// }
	data->gun[0]->enabled = false;
	data->gun[1]->enabled = true;
	ft_usleep(1000);
	data->gun[1]->enabled = false;
	data->gun[2]->enabled = true;
	ft_usleep(100);
	data->gun[2]->enabled = false;
	data->gun[3]->enabled = true;
	ft_usleep(100);
	data->gun[3]->enabled = false;
	data->gun[4]->enabled = true;
	ft_usleep(100);
	data->gun[4]->enabled = false;
	data->gun[0]->enabled = true;
	data->gun_shot = 0;
	write(1, "H\n", 2);
	return (0);
}

/**
 * @brief Unfinished function.
 * 
 * @param data 
 */
void	shoot(t_data *data)
{
	t_raycast	rc;
	pthread_t	anim;
	int			i;

	if (data->gun_shot)
		return ;
	data->gun_shot = 1;
	if (pthread_create(&anim, NULL, gun_shot, data))
		free_all(ERR_MUTEX, 2, data);
	if (data->map->nb_enemy == 0)
		return ;
	get_ray(data, &rc);
	i = is_enemy(data->map, &rc);
	if (i >= 0)
	{
		data->map->enemies[i].life--;
		if (data->map->enemies[i].life == 0)
			data->map->enemies[i].status = 0;
		i++;
	}
}
