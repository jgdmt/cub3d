/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:22:30 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/01 12:44:08 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_all(char *str, int out, t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->lock);
	if (out == 2)
		ft_printf(out, "Error\n");
	if (str)
		ft_printf(out, "%s\n", str);
	if (data->map->map)
		while (data->map->map[i])
			free(data->map->map[i++]);
	free(data->map->map);
	if (data->map->no)
		mlx_delete_image(data->mlx, data->map->no);
	if (data->map->so)
		mlx_delete_image(data->mlx, data->map->so);
	if (data->map->we)
		mlx_delete_image(data->mlx, data->map->we);
	if (data->map->ea)
		mlx_delete_image(data->mlx, data->map->ea);
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	pthread_mutex_unlock(&data->lock);
	pthread_mutex_destroy(&data->lock);
	exit (0);
}
