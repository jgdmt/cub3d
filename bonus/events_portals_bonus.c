/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_portals_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:08:41 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/04 17:13:03 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	shoot_portal(t_data *data, int type)
{
	t_raycast	rc;
	double		x;
	double		y;

	rc.player = *(data->player);
	rc.x = data->width / 2;
	init_ray_param(data->width, &rc);
	step_init(&rc);
	dda(data, &rc);
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

void	debug(t_data *data)
{
	printf("player pos %f %f, dir %f %f\n", data->player->pos.x, data->player->pos.y,
	data->player->dir.x, data->player->dir.y);
	printf("portal blue pos %d %d, dir %d %d\n", data->player->portal[BLUE].pos.x, data->player->portal[BLUE].pos.y,
	data->player->portal[BLUE].dir.x, data->player->portal[BLUE].dir.y);
	printf("portal orange pos %d %d, dir %d %d\n", data->player->portal[ORANGE].pos.x, data->player->portal[ORANGE].pos.y,
	data->player->portal[ORANGE].dir.x, data->player->portal[ORANGE].dir.y);
}

void	shoot(t_data *data)
{
	(void) data;
}

void	portals(mouse_key_t button, action_t act, modifier_key_t mod, void *dt)
{
	t_data	*data;

	(void) mod;
	data = dt;
	if (data->exit)
		return ;
	if (button == MLX_MOUSE_BUTTON_LEFT && act == MLX_PRESS && data->inv == 0)
		shoot_portal(data, BLUE);
	if (button == MLX_MOUSE_BUTTON_RIGHT && act == MLX_PRESS && data->inv == 0)
		shoot_portal(data, ORANGE);
	if (button == MLX_MOUSE_BUTTON_MIDDLE && act == MLX_PRESS && data->inv == 0)
		debug(data);
	if (button == MLX_MOUSE_BUTTON_LEFT && act == MLX_PRESS && data->inv == 1)
		shoot(data);
}

void	scroll(double xdelta, double ydelta, void *gdata)
{
	t_data	*data;

	data = gdata;
	(void) xdelta;
	if (ydelta < 0)
		data->inv = (data->inv + 1) % 2;
	if (ydelta > 0)
		data->inv = data->inv - 1;
	if (data->inv < 0)
		data->inv = 1;
	printf("inventory slot: %i\n", data->inv);
}
