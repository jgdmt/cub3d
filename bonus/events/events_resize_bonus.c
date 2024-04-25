/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_resize_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:36:21 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/25 15:37:05 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief Detect a change in width and height from struct data in comparaison
 * with last call a recreate the data->img(mlx_image_t *).
 * If this function encounter a problem they stop the programm with free_all().
 * 
 * @param data structure with all program data
 */
void	resize_render(t_data *data)
{
	int			i;
	// int			j;
	mlx_image_t	**cursor;
	bool		check;

	cursor = data->cursor;
	free(data->buff);
	check = mlx_resize_image(data->img, data->width, data->height);
	data->buff = malloc(data->width * data->height * sizeof(int));
	if (!check || !data->buff)
		free_all(ERR_MALLOC, 2, data);
	i = 0;
	while (i < 5)
	{
		cursor[i]->instances[0].x = data->width / 2 - cursor[i]->width / 2;
		cursor[i]->instances[0].y = data->height / 2 - cursor[i]->height / 2;
		i++;
	}
	// i = 0;
	// j = i % 6;
	// while (i < 12)
	// {
	// 	data->hud.menu[i]->instances[0].x = data->width / 15;
	// 	if (i == 5)
	// 		j = 3;
	// 	data->hud.menu[i]->instances[0].y = data->height / 3 + j * 60;
	// 	i++;
	// }
}