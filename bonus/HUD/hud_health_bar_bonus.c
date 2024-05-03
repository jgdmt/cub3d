/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_health_bar_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:39:13 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/03 19:28:40 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	print_hp(t_data *data)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	width;

	x = 0;
	width = data->hud.img->width * ((float)data->player->hp / 100);
	while (x < data->hud.img->width)
	{
		y = data->hud.img->height - 15;
		while (y < data->hud.img->height)
		{
			mlx_put_pixel(data->hud.img, x, y, 0xFF000064);
			if (x < width)
				mlx_put_pixel(data->hud.img, x, y, 0xFF0000FF);
			y++;
		}
		x++;
	}
}
