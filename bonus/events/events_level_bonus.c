/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_level_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:33:09 by jgoudema          #+#    #+#             */
/*   Updated: 2024/05/03 20:26:37 by jgoudema         ###   ########.fr       */
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
	data->player->pos.x = 0;
	data->player->pos.y = 0;
	data->map->floor_color = 0;
	data->map->ceiling_color = 0;
	data->map->en_sprites = 0;
	data->map->enemies = 0;
	data->map->nb_enemy = 0;
	data->map->max = 0;
	data->map->door_stat = -1;
	data->map->sp_distance = 0;
	data->map->sp_order = 0;
	data->player->nb = 0;
	data->player->portal[0].status = 0;
	data->player->portal[1].status = 0;
	data->player->portal[0].pos.x = 0;
	data->player->portal[0].pos.y = 0;
	data->player->portal[1].pos.x = 0;
	data->player->portal[1].pos.y = 0;
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
	data->hud.img->enabled = true;
	data->exit = 0;
}

void	show_menu(t_data *data, bool show)
{
	int	i;

	i = 0;
	while (show && i < 5)
	{
		if (i == 3 && data->hud.hidden)
			data->hud.menu[5]->enabled = show;
		else if (i == 0)
			data->hud.menu[i + 6]->enabled = show;
		else
			data->hud.menu[i]->enabled = show;
		i++;
	}
	while (!show && i < 12)
		data->hud.menu[i++]->enabled = show;
}

/**
 * @brief Handles the menu.
 * 
 * @param data structure with all program data
 */
void	menu(t_data *data)
{
	uint32_t	i;

	if (!data->exit)
	{
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
		data->exit = 1;
		ft_usleep(250);
		i = -1;
		while (++i < data->img->width * data->img->height)
			data->img->pixels[(i * 4) + 3] = 125;
		data->hud.img->enabled = false;
		show_menu(data, 1);
	}
	else if (data->exit == 1)
	{
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
		data->exit = 0;
		show_menu(data, 0);
		data->hud.img->enabled = true;
		ft_usleep(250);
	}
}
