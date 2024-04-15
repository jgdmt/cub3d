/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_getbon_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:06:01 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/15 16:02:30 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	fill_door_infos(t_data *data, int x, int y)
{
	if (data->map->door_stat != -1)
		free_all(ERR_DOORS, 2, data);
	data->map->door_stat = 0;
	data->map->door_pos.x = x;
	data->map->door_pos.y = y;
}

void	fill_enemy_infos(t_data *data, int x, int y)
{
	t_map		*map;
	static int	i = 0;

	map = data->map;
	// printf("player %f %f\nenemy %d %d\n %f %f\n", data->player->pos.x - 0.5f, data->player->pos.y - 0.5f, x, y, fabs(data->player->pos.x - 0.5f - x), fabs(data->player->pos.y - 0.5f - y));
	if (fabs(data->player->pos.x - 0.5f - x) < 2
		&& fabs(data->player->pos.y - 0.5f - y) < 2)
		free_all(ERR_ENCLOSE, 2, data);
	if (data->map->nb_enemy > (int)((data->map->max - 2)
		* (data->map->maxy - 2) / 4))
		free_all(ERR_ENEMIES, 2, data);
	map->enemies[i] = malloc(sizeof(t_enemy));
	if (!map->enemies[i])
		free_all(ERR_MALLOC, 2, data);
	map->enemies[i]->pos.x = x;
	map->enemies[i]->pos.y = y;
	map->enemies[i]->status = 0;
	map->enemies[i]->life = 3;
	data->map->map[y][x] = '0';
	i++;
}

void	check_enemy(t_data *data)
{
	int		i;
	t_map	*map;

	if (data->map->nb_enemy == 0)
		return ;
	map = data->map;
	i = 0;
	while (map->enemies && map->enemies[i])
	{
		// printf("check p %f %f\ne %f %f\n %f %f\n", data->player->pos.x - 0.5f, data->player->pos.y - 0.5f, map->enemies[i]->pos.x, map->enemies[i]->pos.y, fabs(data->player->pos.x - 0.5f - map->enemies[i]->pos.x), fabs(data->player->pos.y - 0.5f - map->enemies[i]->pos.y));
		if (fabs(data->player->pos.x - 0.5f - map->enemies[i]->pos.x) < 2
			&& fabs(data->player->pos.y - 0.5f - map->enemies[i]->pos.y) < 2)
			free_all(ERR_ENCLOSE, 2, data);
		i++;
	}
}
