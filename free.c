/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:22:30 by jgoudema          #+#    #+#             */
/*   Updated: 2024/03/13 14:45:24 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(char *str, int out, t_data *data)
{
	int	i;

	i = 0;
	if (str)
		ft_printf(out, "%s", str);
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
	mlx_terminate(data->mlx);
	exit (0);
}
