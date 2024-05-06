/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_getbon_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:06:01 by jgoudema          #+#    #+#             */
/*   Updated: 2024/05/06 16:31:05 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief Fills the informations linked to the eventual door.
 * 
 * @param data structure with all program data
 * @param x coordonate x of the door
 * @param y coordonate y of the door
 */
void	fill_door_infos(t_data *data, int x, int y)
{
	if (data->map->door_stat != -1)
		free_all(ERR_DOORS, 2, data);
	data->map->door_stat = 0;
	data->map->door_pos.x = x;
	data->map->door_pos.y = y;
}

/**
 * @brief Fills the informations linked to the eventual enemies.
 * 
 * @param data structure with all program data
 * @param x coordonate x of the enemy
 * @param y coordonate y of the enemy
 */
void	fill_enemy_infos(t_data *data, double x, double y)
{
	t_map		*map;
	static int	i = 0;

	map = data->map;
	if (fabs(data->player->pos.x - 0.5f - x) < 2
		&& fabs(data->player->pos.y - 0.5f - y) < 2)
		free_all(ERR_ENCLOSE, 2, data);
	if (data->map->nb_enemy > (int)((data->map->max - 2)
		* (data->map->maxy - 2) / 4))
		free_all(ERR_ENEMIES, 2, data);
	map->enemies[i].pos.x = x;
	map->enemies[i].pos.y = y;
	map->enemies[i].status = 1;
	map->enemies[i].life = 3;
	map->enemies[i].flag = 0;
	map->enemies[i].t = map->en_sprites[0];
	map->enemies[i].en_sprites = (mlx_image_t **) map->en_sprites;
	data->map->map[(int)floor(y)][(int)floor(x)] = '0';
	i++;
	if (i == data->map->nb_enemy)
		i = 0;
}

/**
 * @brief Checks if the enemy is not too close to the player.
 * 
 * @param data structure with all program data
 */
void	check_enemy(t_data *data)
{
	int		i;
	t_map	*map;

	if (data->map->nb_enemy == 0)
		return ;
	map = data->map;
	i = 0;
	while (map->enemies && i < map->nb_enemy)
	{
		if (fabs(data->player->pos.x - 0.5f - map->enemies[i].pos.x) < 2
			&& fabs(data->player->pos.y - 0.5f - map->enemies[i].pos.y) < 2)
			free_all(ERR_ENCLOSE, 2, data);
		i++;
	}
}
