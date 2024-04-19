/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_portals_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:08:41 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/19 15:51:14 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief Get the ray object
 * 
 * @param data structure with all program data
 * @param rc ray
 */
void	get_ray(t_data *data, t_raycast *rc)
{
	rc->player = *(data->player);
	rc->x = data->width / 2;
	rc->player.plane.x = 0;
	rc->player.plane.y = 0;
	init_ray_param(data->width, rc);
	step_init(rc);
	dda(data, rc, 40);
}

/**
 * @brief Creates the portal when shot.
 * 
 * @param data structure with all program data
 * @param type portal blue or portal orange
 */
void	shoot_portal(t_data *data, int type)
{
	t_raycast	rc;
	double		x;
	double		y;

	get_ray(data, &rc);
	printf("%i %i\n", rc.ipos.x, rc.ipos.y);
	if (data->player->portal[0].status && data->player->portal[0].pos.x == rc.ipos.x
		&& data->player->portal[0].pos.y == rc.ipos.y)
		return ;
	if (data->player->portal[1].status && data->player->portal[1].pos.x == rc.ipos.x 
		&& data->player->portal[1].pos.y == rc.ipos.y)
		return ;
	x = 0;
	y = 0;
	if (fabs(data->player->dir.x) < fabs(data->player->dir.y))
		y = data->player->dir.y / fabs(data->player->dir.y);
	else
		x = data->player->dir.x / fabs(data->player->dir.x);
	data->player->portal[type].pos.x = rc.ipos.x;
	data->player->portal[type].pos.y = rc.ipos.y;
	data->player->portal[type].dir.x = -x;
	data->player->portal[type].dir.y = -y;
	if (data->player->portal[type].status == 0)
		data->player->portal[type].status = 1;
	printf("player pos %f %f, dir %f %f\n", data->player->pos.x, data->player->pos.y,
	data->player->dir.x, data->player->dir.y);
	printf("portal pos %d %d, dir %d %d\n", data->player->portal[type].pos.x, data->player->portal[type].pos.y,
	data->player->portal[type].dir.x, data->player->portal[type].dir.y);
}

/**
 * @brief Used when the player goes through a portal.
 * 
 * @param data structure with all program data
 * @param to destination portal
 */
void	tp(t_data *data, int to)
{
	int			from;
	t_vector	test;

	from = (to + 1) % 2;

	test.x = (data->player->pos.x - data->player->portal[(to + 1) % 2].pos.x);
	test.y = (data->player->pos.y - data->player->portal[(to + 1) % 2].pos.y);
// 	rotate_vector(&test, &data->player->portal[(to + 1) % 2].dir, &data->player->portal[to].dir);
	if (abs(data->player->portal[to].dir.x) != abs(data->player->portal[from].dir.x))
	{
		data->player->pos.x = test.y + data->player->portal[to].pos.x + (data->player->portal[to].dir.x / 10);
		data->player->pos.y = test.x + data->player->portal[to].pos.y + (data->player->portal[to].dir.y / 10);	
	}
	else
	{
		data->player->pos.x = test.x + data->player->portal[to].pos.x + (data->player->portal[to].dir.x / 10);
		data->player->pos.y = test.y + data->player->portal[to].pos.y + (data->player->portal[to].dir.y / 10);
	}
	rotate_vector(&data->player->dir, &data->player->portal[(to + 1) % 2].dir, &data->player->portal[to].dir);
	rotate_vector(&data->player->plane, &data->player->portal[(to + 1) % 2].dir, &data->player->portal[to].dir);
}

/**
 * @brief Checks if the player goes through a portal or through the door.
 * 
 * @param data structure with all program data
 * @param x coordonate x of the future player position
 * @param y coordonate y of the future player position
 * @return int 
 */
int	check_portal(t_data *data, int x, int y)
{
	t_portal	*port;
	int			i;

	port = data->player->portal;
	i = 0;
	printf("Going to %i %i\n", x, y);
	if (data->map->door_stat == 1 && ((data->map->door_pos.y == y
		&& (fabs(data->map->door_pos.x - x) == 1)) || (data->map->door_pos.x == x
		&& (fabs(data->map->door_pos.y - y) == 1))))
		return (change_map(data), 1);
	while (i < 2)
	{
		if (port[i].status && ((port[i].pos.y == y && (abs(port[i].pos.x - x) == 1))
			|| (port[i].pos.x == x && (abs(port[i].pos.y - y) == 1))))
			if (port[(i + 1) % 2].status)
				// if ((port[i].dir.x && port[1].dir.x * data->player->dir.x < 0) || (port[i].dir.y && port[i].dir.y * data->player->dir.y < 0))
					return (tp(data, (i + 1) % 2), 1);
		i++;
	}
	return (0);
}

/**
 * @brief Resets the portals.
 * 
 * @param data structure with all program data
 */
void	reset_portal(t_data *data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		data->player->portal[i].status = 0;
		data->player->portal[i].pos.y = 0;
		data->player->portal[i].pos.x = 0;
		data->player->portal[i].dir.x = 0;
		data->player->portal[i].dir.y = 0;
		i++;
	}
}
