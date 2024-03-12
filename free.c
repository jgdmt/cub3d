/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:22:30 by jgoudema          #+#    #+#             */
/*   Updated: 2024/03/12 21:06:23 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(char *str, int out, t_data *data)
{
	int	i;

	i = 0;
	if (str)
		ft_printf(out, "%s", str);
	if (data->map_data->map)
		while (data->map_data->map[i])
			free(data->map_data->map[i++]);
	free(data->map_data->map);
	if (data->map_data->no_texture)
		mlx_delete_image(data->mlx, data->map_data->no_texture);
	if (data->map_data->so_texture)
		mlx_delete_image(data->mlx, data->map_data->so_texture);
	if (data->map_data->we_texture)
		mlx_delete_image(data->mlx, data->map_data->we_texture);
	if (data->map_data->ea_texture)
		mlx_delete_image(data->mlx, data->map_data->ea_texture);
	mlx_terminate(data->mlx);
	exit (0);
}
