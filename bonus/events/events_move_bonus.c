/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_move_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:47:44 by jgoudema          #+#    #+#             */
/*   Updated: 2024/05/07 15:31:27 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	collide_enemy(t_data *data, double x, double y)
{
	int			i;
	t_map		*map;

	i = 0;
	map = data->map;
	while (i < data->map->nb_enemy)
	{
		if (map->enemies[i].status && fabs(map->enemies[i].pos.x - x) <= 0.5f \
		&& fabs(map->enemies[i].pos.y - y) <= 0.5f)
			return (1);
		i++;
	}
	return (0);
}

static void	move_xy(t_data *data, t_vector v, t_vector pos)
{
	char	**map;

	map = data->map->map;
	if (data->map->nb_enemy && collide_enemy(data, pos.x + v.x, pos.y + v.y))
	{
		if (fabs((double)data->player->vy) < MAXV)
			data->player->vy = -data->player->vy * 2;
		if (fabs((double)data->player->vx) < MAXV)
			data->player->vx = -data->player->vx * 2;
	}
	if (map[(int)(pos.y + v.y * 2)] \
	[(int)(pos.x + v.x * 2)] == '0' \
	&& map[(int)(pos.y + v.y * 2)] \
	[(int)(pos.x + v.x * 2)] == '0')
	{
		data->player->pos.x += v.x;
		data->player->pos.y += v.y;
	}
	else if (check_portal(data, (pos.x + v.x), (pos.y + v.y), v))
		return ;
}

/**
 * @brief Allows the player to move.
 * 
 * @param data structure with all program data
 */
void	move(t_data *data)
{
	t_vector		v;
	float			theta;

	if (data->player->vx < 10e-7 && data->player->vx > -10e-7 \
	&& data->player->vy < 10e-7 && data->player->vy > -10e-7)
		return ;
	theta = angle(data->player->dir.x, data->player->dir.y, 0, -1);
	v.y = data->player->vx * sin(theta) + data->player->vy * cos(theta);
	v.x = 0;
	move_xy(data, v, data->player->pos);
	v.x = data->player->vx * cos(theta) + data->player->vy * -sin(theta);
	v.y = 0;
	move_xy(data, v, data->player->pos);
}
