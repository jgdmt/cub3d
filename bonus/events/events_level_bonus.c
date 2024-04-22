/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_level_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:33:09 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/22 21:00:34 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief Reinitializes the values of the data structure.
 * 
 * @param data structure with all program data
 */
void	reinit_data(t_data *data)
{
	data->map->map = 0;
	data->map->no = 0;
	data->map->so = 0;
	data->map->we = 0;
	data->map->ea = 0;
	data->map->floor_color = 0;
	data->map->ceiling_color = 0;
	data->map->en_sprites = 0;
	data->map->enemies = 0;
	data->map->max = 0;
	data->map->door_stat = -1;
	data->player->nb = 0;
	data->player->portal[0].status = 0;
	data->player->portal[1].status = 0;
}

/**
 * @brief Changes the (char **) data::map::map with the next, if it exists.
 * 
 * @param data structure with all program data
 */
void	change_map(t_data *data, int np)
{
	static int	i = 1;
	t_map		*map;

	data->exit = 2;
	ft_usleep(250);
	map = data->map;
	reinit_data(data);
	free_smap(data->mlx, map);
	i = i + np;
	if (data->argv[i] && i > 0)
		parsing(data->argv[i], data);
	else
		free_all(MSG_END, 1, data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	data->exit = 0;
}

/**
 * @brief Handles the menu.
 * 
 * @param data structure with all program data
 */
void	menu(t_data *data)
{
	static int	paused = 0;

	if (!paused)
	{
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
		data->exit = 1;
		data->img->enabled = false;
		ft_usleep(250);
		paused = 1;
	}
	else
	{
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
		data->exit = 0;
		data->img->enabled = true;
		ft_usleep(250);
		paused = 0;
	}
}
