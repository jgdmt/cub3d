/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_main_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:10:19 by jgoudema          #+#    #+#             */
/*   Updated: 2024/05/06 12:26:37 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	door_event(t_data *data)
{
	int	i;

	i = -1;
	if (fabs(data->player->pos.x - data->map->door_pos.x) < 2.5
		&& fabs(data->player->pos.y - data->map->door_pos.y) < 2.5)
	{
		while (++i < data->map->nb_enemy)
			if (data->map->enemies[i].status)
				return ;
		if (data->map->door_stat)
			data->map->door_stat = 0;
		else
			data->map->door_stat = 1;
	}
}

/**
 * @brief Handles the possible inputs.
 * 
 * @param gdata structure with all program data
 */
void	hook(void *gdata)
{
	t_data			*data;

	data = gdata;
	if (data->player->hp <= 0)
		free_all(MSG_DEATH, 1, data);
	if (data->exit == 3)
		change_map(data, 1);
	if (data->exit)
		return ;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate(RSPEED, data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate(-RSPEED, data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) && data->player->vy > -MAXV)
		data->player->vy -= ACCELERATION;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) && data->player->vy < MAXV)
		data->player->vy += ACCELERATION;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) && data->player->vx < MAXV)
		data->player->vx += ACCELERATION;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D) && data->player->vx > -MAXV)
		data->player->vx -= ACCELERATION;
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE) && !data->player->vz)
		data->player->vz += 5;
	mouse_move(gdata);
}

/**
 * @brief Handles the closing of the window.
 * 
 * @param gdata structure with all program data
 */
void	close_window(void *gdata)
{
	t_data	*data;

	data = gdata;
	free_all("Game closed", 1, data);
}
