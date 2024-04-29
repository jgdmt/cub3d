/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:27:54 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/29 18:51:10 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	init_data_values(t_data *data)
{
	int	i;

	i = 0;
	while (i < 12)
	{
		if (i < 10)
			data->portal_gun[i] = 0;
		if (i < 5)
			data->cursor[i] = 0;
		if (i < 5)
			data->gun[i] = 0;
		if (i < 4)
			data->portal[i] = 0;
		data->hud.menu[i] = 0;
		i++;
	}
}

void	init_data_texture(t_data *data, mlx_t *mlx)
{
	mlx_texture_t	*loading;

	loading = mlx_load_png("./bonus/assets/icon.png");
	if (!loading)
		free_all(ERR_MLX, 2, data);
	data->loading = mlx_texture_to_image(mlx, loading);
	mlx_delete_texture(loading);
	if (!data->loading)
		free_all(ERR_MLX, 2, data);
	if (mlx_image_to_window(mlx, data->loading, 704, 284) == -1)
		free_all(ERR_MLX, 2, data);
	data->loading->enabled = false;
	init_data_values(data);
	init_door_text(data, mlx);
	init_portals_text(data, mlx);
	init_hud_text(data, mlx);
	init_cursor_text(data, mlx);
	init_portalgun_text(data, mlx);
	init_gun_text(data, mlx);
}

t_data	init_data(t_map *map, t_player *player, mlx_t *mlx, char **argv)
{
	t_data			data;

	data.player = player;
	data.map = map;
	data.mlx = mlx;
	data.width = WIDTH;
	data.height = HEIGHT;
	data.img = 0;
	data.exit = 0;
	data.inv = 0;
	data.loading = 0;
	data.gun_shot = 0;
	data.portal_shot = -1;
	data.argv = argv;
	data.hud.hidden = 0;
	data.hud.width = 566;
	data.hud.heigth = 576;
	data.loading = 0;
	init_data_texture(&data, mlx);
	return (data);
}
