/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datatext_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:42:15 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/29 15:16:02 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

mlx_image_t	*create_image(mlx_t *mlx, char*(text)(int), int i)
{
	mlx_texture_t	*curr;
	mlx_texture_t	*tmp;
	mlx_image_t		*img;

	curr = mlx_load_png(text(i));
	if (!curr)
		return (NULL);
	tmp = curr;
	img = mlx_texture_to_image(mlx, curr);
	if (!img)
		return (mlx_delete_texture(tmp), NULL);
	mlx_delete_texture(tmp);
	return (img);
}

void	init_hud_text(t_data *data, mlx_t *mlx)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < 12)
	{
		data->hud.menu[i] = create_image(mlx, assets_hud, i);
		if (!data->hud.menu[i])
			free_all(ERR_MLX, 2, data);
		j = i % 6;
		if (j == 5)
			j = 3;
		if (mlx_image_to_window(mlx, data->hud.menu[i], data->width / 15,
				(data->height - 350) / 2 + j * 70) == -1)
			free_all(ERR_MLX, 2, data);
		data->hud.menu[i]->instances[0].z = 10;
		data->hud.menu[i]->enabled = false;
		i++;
	}
}

void	init_door_text(t_data *data, mlx_t *mlx)
{
	data->map->door_close = create_image(mlx, assets_doors, 0);
	data->map->door_open = create_image(mlx, assets_doors, 1);
	if (!data->map->door_close || !data->map->door_open)
		free_all(ERR_MLX, 2, data);
}

void	init_cursor_text(t_data *data, mlx_t *mlx)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		data->cursor[i] = create_image(mlx, assets_cursor, i);
		if (!data->cursor[i])
			free_all(ERR_MLX, 2, data);
		if (mlx_image_to_window(mlx, data->cursor[i], data->width / 2
				- data->cursor[i]->width / 2, data->height / 2
				- data->cursor[i]->height / 2) == -1)
			free_all(ERR_MLX, 2, data);
		data->cursor[i]->instances[0].z = 25;
		data->cursor[i]->enabled = false;
		i++;
	}
}

void	init_portals_text(t_data *data, mlx_t *mlx)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->portal[i] = create_image(mlx, assets_portals, i);
		if (!data->portal[i])
			free_all(ERR_MLX, 2, data);
		i++;
	}
}
