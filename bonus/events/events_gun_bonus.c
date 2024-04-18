/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_gun_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:36:49 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/18 14:26:46 by jgoudema         ###   ########.fr       */
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
	while (map->enemies[i])
	{
		if (map->enemies[i]->status && map->enemies[i]->pos.x == rc->ipos.x
			&& map->enemies[i]->pos.y == rc->ipos.y)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Unfinished function.
 * 
 * @param data 
 */
void	shoot(t_data *data)
{
	t_raycast	rc;
	int			i;

	if (data->map->nb_enemy == 0)
		return ;
	get_ray(data, &rc);
	i = is_enemy(data->map, &rc);
	if (i >= 0)
	{
		data->map->enemies[i]->life--;
		if (data->map->enemies[i]->life == 0)
			data->map->enemies[i]->status = 0;
		i++;
	}
}
