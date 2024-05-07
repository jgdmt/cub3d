/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_portals_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:08:41 by jgoudema          #+#    #+#             */
/*   Updated: 2024/05/07 17:35:29 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	*portal_shot(void *gdata)
{
	int		i;
	t_data	*data;
	int		type;

	data = gdata;
	i = 0;
	type = 4 * data->portal_shot;
	data->portal_gun[0]->enabled = false;
	while (i < 4)
	{
		data->portal_gun[i + type]->enabled = false;
		data->portal_gun[i + type + 1]->enabled = true;
		i++;
		ft_usleep(80);
	}
	data->portal_gun[i + type]->enabled = false;
	data->portal_gun[0]->enabled = true;
	data->portal_shot = -1;
	return (0);
}

void	shoot_portal_xy(t_data *data, t_raycast rc, int *x, int *y)
{
	*x = 0;
	*y = 0;
	if (rc.side == 0)
	{
		*x = 1;
		if (rc.ipos.x > data->player->pos.x)
			*x = -1;
	}
	else
		*y = -data->player->dir.y / fabs(data->player->dir.y);
}

/**
 * @brief Creates the portal when shot.
 * 
 * @param data structure with all program data
 * @param type portal blue or portal orange
 */
void	shoot_portal(t_data *data, int type, int other)
{
	t_raycast	rc;
	pthread_t	panim;
	t_portal	*p;
	int			x;
	int			y;

	if (data->portal_shot != -1)
		return ;
	data->portal_shot = type;
	p = data->player->portal;
	if (pthread_create(&panim, NULL, portal_shot, data))
		free_all(ERR_MUTEX, 2, data);
	get_ray(data, &rc);
	shoot_portal_xy(data, rc, &x, &y);
	if ((p[other].status && p[other].dir.x == x && p[other].dir.y == y \
		&& p[other].pos.x == rc.ipos.x && p[other].pos.y == rc.ipos.y) \
		|| (data->map->door_stat >= 0 && data->map->door_pos.x == rc.ipos.x \
		&& data->map->door_pos.y == rc.ipos.y))
		return ;
	p[type].pos.x = rc.ipos.x;
	p[type].pos.y = rc.ipos.y;
	p[type].dir.x = x;
	p[type].dir.y = y;
	if (p[type].status == 0)
		p[type].status = 1;
}

/**
 * @brief Checks if the player goes through a portal or through the door.
 * 
 * @param data structure with all program data
 * @param x coordonate x of the future player position
 * @param y coordonate y of the future player position
 * @return int 
 */
int	check_portal(t_data *data, double x, double y, t_vector v)
{
	t_portal	*port;
	int			i;

	port = data->player->portal;
	i = 0;
	if (data->map->door_stat == 1 && \
	fabs(data->map->door_pos.x + 0.5 - x) < 0.7 \
	&& fabs(data->map->door_pos.y + 0.5 - y) < 0.7)
	{
		data->exit = LOADING;
		return (1);
	}
	while (i < 2)
	{
		if (port[i].status && port[(i + 1) % 2].status \
		&& (fabs(port[i].pos.x + 0.5 - x) < 0.56 \
		&& fabs(port[i].pos.y + 0.5 - y) < 0.56))
			if ((port[i].dir.x && port[i].dir.x * v.x < 0) \
				|| (port[i].dir.y && port[i].dir.y * v.y < 0))
				return (tp(data, (i + 1) % 2, i), 1);
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
