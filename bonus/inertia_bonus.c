/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inertia_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:24:32 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/06 16:12:37 by vilibert         ###   ########.fr       */
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

void	moving(t_data *data, t_enemy *enemy, int i)
{
	if ((fabs(enemy->pos.x - data->player->pos.x) > 13 \
	|| fabs(enemy->pos.y - data->player->pos.y) > 13))
		return ;
	if (data->player->pos.x - enemy->pos.x < 0 \
	&& is_enemy(data, enemy->pos.x - 0.02f, enemy->pos.y, i) == -1)
		data->map->enemies[i].pos.x -= 0.02f;
	else if (data->player->pos.x - enemy->pos.x > 0 \
	&& is_enemy(data, enemy->pos.x + 0.02f, enemy->pos.y, i) == -1)
		enemy->pos.x += 0.02f;
	if (data->player->pos.y - enemy->pos.y < 0 \
	&& is_enemy(data, enemy->pos.x, enemy->pos.y - 0.02f, i) == -1)
		enemy->pos.y -= 0.02f;
	else if (data->player->pos.y - enemy->pos.y > 0 \
	&& is_enemy(data, enemy->pos.x, enemy->pos.y + 0.02f, i) == -1)
		enemy->pos.y += 0.02f;
}

void	refresh_enemy(t_data *data)
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

static void	inertia(t_data *data)
{
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

/**
 * @brief Slow the player by tends data::player::vx and 
 * data::player::vy towards 0.
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
	while (data->exit != EXIT)
	{
		if (!data->exit)
		{
			refresh_enemy(data);
			move(data);
			inertia(data);
		}
		time = get_time();
		if (time - last_time < 13)
			ft_usleep(13 - (time - last_time));
		last_time = time;
	}
	return (NULL);
}
