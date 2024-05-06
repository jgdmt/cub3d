/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:22:30 by jgoudema          #+#    #+#             */
/*   Updated: 2024/05/06 17:38:33 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	destroy(mlx_t *mlx, mlx_image_t	**imgs, int i)
{
	int	j;

	j = 0;
	while (j < i && imgs[j])
	{
		mlx_delete_image(mlx, imgs[j]);
		j++;
	}
}

void	free_smap(mlx_t *mlx, t_map *map)
{
	free_array(map->map);
	free(map->enemies);
	free(map->sp_distance);
	free(map->sp_order);
	if (map->nb_enemy)
		destroy(mlx, map->en_sprites, 4);
	if (map->no)
		mlx_delete_image(mlx, map->no);
	if (map->so)
		mlx_delete_image(mlx, map->so);
	if (map->we)
		mlx_delete_image(mlx, map->we);
	if (map->ea)
		mlx_delete_image(mlx, map->ea);
	if (map->ceiling_color)
		mlx_delete_image(mlx, map->ceiling_color);
	if (map->floor_color)
		mlx_delete_image(mlx, map->floor_color);
}

void	free_all(char *str, int out, t_data *data)
{
	if (data->exit == EXIT)
		return ;
	data->exit = EXIT;
	if (out == 2)
		ft_printf(out, "Error\n");
	if (str)
		ft_printf(out, "%s\n", str);
	ft_usleep(250);
	pthread_join(data->threads[0], NULL);
	pthread_join(data->threads[1], NULL);
	pthread_join(data->threads[2], NULL);
	free_smap(data->mlx, data->map);
	if (data->map->door_open)
		mlx_delete_image(data->mlx, data->map->door_open);
	if (data->map->door_close)
		mlx_delete_image(data->mlx, data->map->door_close);
	destroy(data->mlx, data->cursor, 5);
	destroy(data->mlx, data->portal, 4);
	destroy(data->mlx, data->hud.menu, 12);
	destroy(data->mlx, data->portal_gun, 10);
	destroy(data->mlx, data->gun, 5);
	if (data->loading)
		mlx_delete_image(data->mlx, data->loading);
	free(data->hud.buff);
	if (data->buff)
		free(data->buff);
	if (data->hud.img)
		mlx_delete_image(data->mlx, data->hud.img);
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	exit (0);
}
