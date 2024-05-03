/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_move_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:47:44 by jgoudema          #+#    #+#             */
/*   Updated: 2024/05/03 20:11:28 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	collide_enemy(t_data *data, double x, double y)
{
	int			i;
	pthread_t	sprite;
	t_map		*map;

	i = 0;
	map = data->map;
	while (i < data->map->nb_enemy)
	{
		if (map->enemies[i].status && fabs(map->enemies[i].pos.x - x) <= 0.5f \
		&& fabs(map->enemies[i].pos.y - y) <= 0.5f)
		{
			pthread_create(&sprite, NULL, atk_sprite, (void *)&map->enemies[i]);
			data->player->hp -= 11;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	move_xy(t_data *data, t_int_vector sign, t_vector v, t_vector pos)
{
	char	**map;

	map = data->map->map;
	if (data->map->nb_enemy && collide_enemy(data, pos.x + v.x, pos.y + v.y))
	{
		data->player->vy = -data->player->vy * 2;
		data->player->vx = -data->player->vx * 2;
		return (1);
	}
	else if (map[(int)(pos.y + sign.y * 0.1 + v.y * 2)] \
	[(int)(pos.x + sign.x + v.x * 2)] == '0'
		&& map[(int)(pos.y - sign.y * 0.1 + v.y * 2)] \
		[(int)(pos.x - sign.x + v.x * 2)] == '0')
	{
		data->player->pos.x += v.x;
		data->player->pos.y += v.y;
	}
	else
	{
		if (check_portal(data, floor(pos.x + v.x), floor(pos.y), v))
			return (1);
		data->player->vx = data->player->vx * (v.y != 0);
		data->player->vy = data->player->vy * (v.x != 0);
	}
	return (0);
}

/**
 * @brief Allows the player to move.
 * 
 * @param data structure with all program data
 */
void	move(t_data *data)
{
	t_int_vector	sign;
	t_vector		v;
	float			theta;

	if (data->player->vx < 10e-7 && data->player->vx > -10e-7 \
	&& data->player->vy < 10e-7 && data->player->vy > -10e-7)
		return ;
	theta = angle(data->player->dir.x, data->player->dir.y, 0, -1);
	sign.y = 0;
	sign.x = 0;
	if (fabs(v.x) == 1)
		sign.x = v.x;
	v.x = data->player->vx * cos(theta) + data->player->vy * -sin(theta);
	v.y = 0;
	move_xy(data, sign, v, data->player->pos);
	if (fabs(v.y) == 1)
		sign.y = v.y;
	sign.x = 0;
	v.y = data->player->vx * sin(theta) + data->player->vy * cos(theta);
	v.x = 0;
	move_xy(data, sign, v, data->player->pos);
}
