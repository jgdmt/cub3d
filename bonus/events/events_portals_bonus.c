/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_portals_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:08:41 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/16 11:17:33 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	get_ray(t_data *data, t_raycast *rc)
{
	rc->player = *(data->player);
	rc->x = data->width / 2;
	init_ray_param(data->width, rc);
	step_init(rc);
	dda(data, rc);
}

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

void	tp(t_data *data, int to)
{

	data->player->pos.x = data->player->portal[to].pos.x + data->player->portal[to].dir.x;
	data->player->pos.y = data->player->portal[to].pos.y + data->player->portal[to].dir.y;
	rotate_vector(&data->player->dir, &data->player->portal[(to + 1) % 2].dir, &data->player->portal[to].dir);
	rotate_vector(&data->player->plane, &data->player->portal[(to + 1) % 2].dir, &data->player->portal[to].dir);
}

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
				return (tp(data, (i + 1) % 2), 1);
		i++;
	}
	return (0);
}
