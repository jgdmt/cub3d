/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:22:30 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/09 20:08:59 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_smap(mlx_t *mlx, t_map *map)
{
	int	i;

	i = 0;
	if (map->map)
		while (map->map[i])
			free(map->map[i++]);
	free(map->map);
	i = 0;
	if (map->enemies)
		while (map->enemies[i])
			free(map->enemies[i++]);
	free(map->enemies);
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
	int	i;

	i = 0;
	// pthread_mutex_lock(&data->lock);
	data->exit = 1;
	if (out == 2)
		ft_printf(out, "Error\n");
	if (str)
		ft_printf(out, "%s\n", str);
	ft_usleep(250);
	free_smap(data->mlx, data->map);
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	// pthread_mutex_unlock(&data->lock);
	pthread_mutex_destroy(&data->lock);
	exit (0);
}
