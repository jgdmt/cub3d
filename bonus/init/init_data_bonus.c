/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:27:54 by jgoudema          #+#    #+#             */
/*   Updated: 2024/05/02 14:14:35 by vilibert         ###   ########.fr       */
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

	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	loading = mlx_load_png("./bonus/assets/icon.png");
	if (!loading || !data->img)
		free_all(ERR_MLX, 2, data);
	data->loading = mlx_texture_to_image(mlx, loading);
	mlx_delete_texture(loading);
	if (!data->loading)
		free_all(ERR_MLX, 2, data);
	if (mlx_image_to_window(mlx, data->img, 0, 0) == -1)
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

void	init_data_hud(t_data *data)
{
	data->hud.width = 360;
	data->hud.height = 375;
	data->hud.img = mlx_new_image(data->mlx, data->hud.width, data->hud.height);
	data->hud.buff = malloc(data->hud.width * (data->hud.height - 15) * \
	sizeof(uint32_t));
	if (!data->hud.img || !data->hud.buff)
		free_all(ERR_MALLOC, 2, data);
	if (mlx_image_to_window(data->mlx, data->hud.img, 0, 0) == -1)
		free_all(ERR_MLX, 2, data);
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
	data.loading = 0;
	data.hud.buff = 0;
	init_data_texture(&data, mlx);
	init_data_hud(&data);
	return (data);
}
