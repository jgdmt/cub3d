/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:51:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/01 16:05:22 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	get_minimap(t_data *data)
{
	t_vector	pos;
	t_vector	temp_pos;
	t_vector	delta;
	int			i;
	int			j;

	delta.x = (double)10 / data->hud.width;
	delta.y = (double)10 / (data->hud.height - 15);
	temp_pos = data->player->pos;
	pos = temp_pos;
	pos.y -= 5;
	i = 0;
	while (i < data->hud.height - 15)
	{
		j = data->hud.width - 1;
		pos.x = temp_pos.x - 5;
		while (j >= 0)
		{
			if (pos.x < 0 || pos.y < 0 || !data->map->map[(int)floor(pos.y)][(int)floor(pos.x)])
				mlx_put_pixel(data->hud_img, j, i, 0x000000ff);
			else if (data->map->map[(int)floor(pos.y)][(int)floor(pos.x)] == '1')
				mlx_put_pixel(data->hud_img, j, i, 0x000000ff);
			else if (data->map->map[(int)floor(pos.y)][(int)floor(pos.x)] == '0')
				mlx_put_pixel(data->hud_img, j, i, 0xffffffff);
			else
				mlx_put_pixel(data->hud_img, j, i, 0x000000ff);
			if (data->player->portal[0].status == 1 && data->player->portal[0].pos.x == floor(pos.x) && data->player->portal[0].pos.y == floor(pos.y))
				mlx_put_pixel(data->hud_img, j, i, 0x04dcfcff);
			else if (data->player->portal[1].status == 1 && data->player->portal[1].pos.x == floor(pos.x) && data->player->portal[1].pos.y == floor(pos.y))
				mlx_put_pixel(data->hud_img, j, i, 0xfc9c04ff);
			
			if ((pos.x > 0 && pos.y > 0 && data->map->map[(int)floor(pos.y)][(int)floor(pos.x)]) || pos.x < 0)
			pos.x += delta.x;
			j--;
		}
		if ((pos.x > 0 && pos.y > 0 && data->map->map[(int)ceil(pos.y)]) || pos.y < 0)
			pos.y += delta.y;
		i++;
	}
}
