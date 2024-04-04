/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_getbon_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:06:01 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/04 21:53:42 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	fill_door_infos(t_data *data, int x, int y)
{
	if (data->map->door.status != -1)
		free_all(ERR_DOORS, 2, data);
	data->map->door.status = 0;
	data->map->door.pos.x = x;
	data->map->door.pos.y = y;
}

void	fill_enemy_infos(t_data *data, int x, int y)
{
	// printf("player %f %f\nenemy %d %d\n %f %f\n", data->player->pos.x, data->player->pos.y, x, y, fabs(data->player->pos.x - x), fabs(data->player->pos.y - y));
	if (fabs(data->player->pos.x - x) < 2 && fabs(data->player->pos.y - y) < 2) //not working :/
		free_all(ERR_ENCLOSE, 2, data);
	if (data->map->nb_enemy > (int)((data->map->max - 2) * (data->map->maxy - 2) / 4))
		free_all(ERR_ENEMIES, 2, data);
	data->map->nb_enemy++;
}
