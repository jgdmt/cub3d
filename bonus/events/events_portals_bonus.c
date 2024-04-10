/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_portals_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:08:41 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/10 17:01:38 by jgoudema         ###   ########.fr       */
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
	int	sign;

	data->exit = 2;
	ft_usleep(250);
	data->player->pos.x = data->player->portal[to].pos.x + data->player->portal[to].dir.x;
	data->player->pos.y = data->player->portal[to].pos.y + data->player->portal[to].dir.y;
	data->player->dir.x = data->player->portal[to].dir.x;
	data->player->dir.y = data->player->portal[to].dir.y;
	sign = -1;
	if (data->player->portal[to].dir.x == 0)
		sign = 1;
	data->player->plane.x = sign * data->player->portal[to].dir.y;
	data->player->plane.y = sign * data->player->portal[to].dir.x;
	data->exit = 0;
}

int	check_portal(t_data *data, int x, int y)
{
	t_portal	*port;
	int			i;

	port = data->player->portal;
	i = 0;
	printf("Going to %i %i\n", x, y);
	while (i < 2)
	{
		if (port[i].status && ((port[i].pos.y == y && (port[i].pos.x == x + 1
						|| port[i].pos.x == x - 1)) || (port[i].pos.x == x
					&& (port[i].pos.y == y + 1 || port[i].pos.y == y - 1))))
		{
			if (i == BLUE && port[ORANGE].status)
				return (tp(data, ORANGE), 1);
			if (i == ORANGE && port[BLUE].status)
				return (tp(data, BLUE), 1);
		}
		i++;
	}
	return (0);
}
