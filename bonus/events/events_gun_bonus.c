/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_gun_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:36:49 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/30 20:47:48 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	is_enemy(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map->nb_enemy)
	{
		// printf("%i %d %i %d %i\n", i, (int) data->map->enemies[i].pos.x, x, (int) data->map->enemies[i].pos.y, y);
		if (data->map->enemies[i].status && (int) data->map->enemies[i].pos.x == x && (int) data->map->enemies[i].pos.y == y)
			return (i);
		i++;
	}
	return (-1);
}

static int	dda_enemy(t_data *data, t_raycast *rc)
{
	int	i;

	while (1)
	{
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta_dist.x;
			rc->ipos.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			rc->ipos.y += rc->step.y;
			rc->side = 1;
		}
		if (data->map->map[rc->ipos.y][rc->ipos.x] == '1' || data->map->map[rc->ipos.y][rc->ipos.x] == '2')
			return (-1);
		else
		{
			i = is_enemy(data, rc->ipos.x, rc->ipos.y);
			if (i >= 0)
				return (i);
		}
	}
}

int	get_enemy_ray(t_data *data, t_raycast *rc)
{
	rc->player = *(data->player);
	rc->x = data->width / 2;
	rc->player.plane.x = 0;
	rc->player.plane.y = 0;
	init_ray_param(data->width, rc);
	step_init(rc);
	return (dda_enemy(data, rc));
}

/**
 * @brief Unfinished function.
 * 
 * @param map 
 * @param rc 
 * @return int 
 */
// int	is_enemy(t_player *player, t_map *map, t_raycast *rc)
// {
// 	int		i;
// 	double	delta;
// 	double	p;

// 	// y = mx + p -> y = ()
// 	i = 0;
// 	delta = (rc->ipos.y - player->pos.y) / (rc->ipos.x - player->pos.x);
// 	p = rc->ipos.y - rc->ipos.x * delta;
// 	// printf("%d %d %f %f\n", rc->ipos.x, rc->ipos.y, rc->ray_dir.x, rc->ray_dir.y);
// 	while (i < map->nb_enemy)
// 	{
// 		printf("%i %i %f %f %f %i\n", i, map->enemies[i].status, map->enemies[i].pos.y, delta * map->enemies[i].pos.x + p,  floor(fabs(map->enemies[i].pos.y - delta * map->enemies[i].pos.x + p)), floor(fabs(map->enemies[i].pos.y - delta * map->enemies[i].pos.x + p)) < 1);
// 		if (map->enemies[i].status && floor(fabs(map->enemies[i].pos.y - delta * map->enemies[i].pos.x + p)) < 1)
// 			return (i);
// 		// if (map->enemies[i].status && map->enemies[i].pos.x == rc->ipos.x
// 		// 	&& map->enemies[i].pos.y == rc->ipos.y)
// 		// 	return (i);
// 		i++;
// 	}
// 	return (-1);
// }

void	*gun_shot(void *gdata)
{
	t_data	*data;
	int		i;

	data = gdata;
	i = 0;
	while (i < 4)
	{
		data->gun[i]->enabled = false;
		data->gun[i + 1]->enabled = true;
		i++;
		ft_usleep(80);
	}
	// ft_usleep(80);
	data->gun[4]->enabled = false;
	data->gun[0]->enabled = true;
	data->gun_shot = 0;
	return (0);
}

/**
 * @brief Unfinished function.
 * 
 * @param data 
 */
void	shoot(t_data *data)
{
	t_raycast	rc;
	pthread_t	anim;
	int			i;

	if (data->gun_shot)
		return ;
	data->gun_shot = 1;
	if (pthread_create(&anim, NULL, gun_shot, data))
		free_all(ERR_MUTEX, 2, data);
	if (data->map->nb_enemy == 0)
		return ;
	i = get_enemy_ray(data, &rc);
	printf("i %i\n", i);
	if (i >= 0)
	{
		printf("But... What are you doing? Stop it!\n");
		data->map->enemies[i].life--;
		if (data->map->enemies[i].life == 0)
			data->map->enemies[i].status = 0;
		i++;
	}
}
