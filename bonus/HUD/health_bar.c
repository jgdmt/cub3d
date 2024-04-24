/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:39:13 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/24 13:27:59 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	print_hp(t_data *data)
{
	int	x;
	int	y;
	int width;

	x = 0;
	width = 200 * ((float)data->player->hp / 100);
	while (x < width)
	{
		y = 190;
		while (y < 200)
		{
			mlx_put_pixel(data->hud_img, x, y, 0xFF0000FF);
			y++;
		}
		x++;
	}
	while (x < 200)
	{
		y = 190;
		while (y < 200)
		{
			mlx_put_pixel(data->hud_img, x, y, 0xFF000064);
			y++;
		}
		x++;
	}
}
