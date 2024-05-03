/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inertia_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:24:32 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/03 18:19:14 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	anim_enemy(t_enemy *enemy, int *i)
{
	if (enemy->flag)
		return ;
	enemy->t = enemy->en_sprites[*i];
	(*i)++;
	if (*i > 2)
		*i = 0;
}

int	is_enemy3(t_data *data, double x, double y, int j)
{
	int	i;

	i = 0;
	while (i < data->map->nb_enemy)
	{
		if (i != j && data->map->enemies[i].status\
		&& (fabs(data->map->enemies[i].pos.x - x) < 1 \
		&& fabs(data->map->enemies[i].pos.y - y) < 1))
			return (1);
		i++;
	}
	return (0);
}

void	moving(t_data *data, t_enemy *enemy, int i)
{
	if ((fabs(enemy->pos.x - data->player->pos.x) > 13 || fabs(enemy->pos.y - data->player->pos.y) > 13))
		return ;
	if (data->player->pos.x - enemy->pos.x < 0 && !is_enemy3(data, enemy->pos.x - 0.02f, enemy->pos.y, i))
		data->map->enemies[i].pos.x -= 0.02f;
	else if (data->player->pos.x - enemy->pos.x > 0 && !is_enemy3(data, enemy->pos.x + 0.02f, enemy->pos.y, i))
		enemy->pos.x += 0.02f;
	if (data->player->pos.y - enemy->pos.y < 0 && !is_enemy3(data, enemy->pos.x, enemy->pos.y - 0.02f, i))
		enemy->pos.y -= 0.02f;
	else if (data->player->pos.y - enemy->pos.y > 0 && !is_enemy3(data, enemy->pos.x, enemy->pos.y + 0.02f, i))
		enemy->pos.y += 0.02f;
}

void	move_enemy(t_data *data)
{
	int			i;
	static int	j = 0;
	static int	k = 0;

	i = 0;
	if (k < 100)
		k++;
	while (i < data->map->nb_enemy)
	{
		moving(data, &data->map->enemies[i], i);
		if (k == 100)
			anim_enemy(&data->map->enemies[i], &j);
		i++;
	}
	if (k >= 100)
		k = 0;
}

/**
 * @brief Slow the player by tends data::player::vx and data::player::vy towards 0.
 * 
 * @param data structure with all program data
 */
void	*update_inertia(void *gdata)
{
	t_data	*data;
	size_t	last_time;
	size_t	time;

	data = gdata;
	last_time = get_time();
	while (1)
	{
		if (!data->exit)
		{
			// check_death(data);
			move_enemy(data);
			move(data);
			data->player->posz += data->player->vz;
			if (data->player->posz > 0)
				data->player->vz -= INERTIA * 100;
			if (data->player->posz == 0)
				data->player->vz = 0;
			if (data->player->vx > 10e-8)
				data->player->vx -= INERTIA;
			else if (data->player->vx < -10e-8)
				data->player->vx += INERTIA;
			if (data->player->vy > 10e-8)
				data->player->vy -= INERTIA;
			else if (data->player->vy < -10e-8)
				data->player->vy += INERTIA;
		}
		time = get_time();
		if (time - last_time < 13)
			ft_usleep(13 - (time - last_time));
		last_time = time;
	}
}
