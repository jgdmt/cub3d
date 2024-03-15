/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:27:43 by vilibert          #+#    #+#             */
/*   Updated: 2024/03/15 12:29:07 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_tex_ptr(t_data *data, t_raycast *rc)
{
	if (rc->ipos.x >= data->player->pos.x && rc->side == 0)
	{
		rc->t = data->map->ea;
	}
	if (rc->ipos.x < data->player->pos.x && rc->side == 0)
	{
		rc->t = data->map->we;
	}
	if (rc->ipos.y >= data->player->pos.y && rc->side == 1)
	{
		rc->t = data->map->no;
	}
	if (rc->ipos.y < data->player->pos.y && rc->side == 1)
	{
		rc->t = data->map->so;
	}
}
