/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:39:13 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/01 11:29:36 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	print_hp(t_data *data)
{
	int	x;
	int	y;
	int	width;

	x = 0;
	width = data->hud.width * ((float)data->player->hp / 100);
	while (x < data->hud.width)
	{
		y = data->hud.height - 15;
		while (y < data->hud.height)
		{
			mlx_put_pixel(data->hud_img, x, y, 0xFF000064);
			if (x < width)
				mlx_put_pixel(data->hud_img, x, y, 0xFF0000FF);
			y++;
		}
		x++;
	}
}
