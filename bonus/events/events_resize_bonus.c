/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_resize_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:36:21 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/02 17:15:58 by vilibert         ###   ########.fr       */
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
	int			j;
	mlx_image_t	**cursor;
	bool		check[2];

	printf("%i %i\n", data->width, data->height);
	cursor = data->cursor;
	free(data->buff);
	free(data->hud.buff);
	data->hud.height = data->height / 3 + 15;
	data->hud.width = data->hud.height - 15;
	check[0] = mlx_resize_image(data->img, data->width, data->height);
	check[1] = mlx_resize_image(data->hud.img, data->hud.width, data->hud.height);
	data->buff = malloc(data->width * data->height * sizeof(int));
	data->hud.buff = malloc(data->hud.width * (data->hud.height - 15) * sizeof(uint32_t));
	if (!check[0]  || !check[1] || !data->buff)
		free_all(ERR_MALLOC, 2, data);
	i = 0;
	while (i < data->hud.height * data->hud.width)
		data->hud.img->pixels[i++ * 4 + 3] = 0x00;
	i = 0;
	while (i < 5)
	{
		cursor[i]->instances[0].x = data->width / 2 - cursor[i]->width / 2;
		cursor[i]->instances[0].y = data->height / 2 - cursor[i]->height / 2;
		i++;
	}
	i = 0;
	while (i < 12)
	{
		j = i % 6;
		data->hud.menu[i]->instances->x = data->width / 15;
		if (j == 5)
			j = 3;
		data->hud.menu[i]->instances->y = (data->height - 350) / 2 + j * 70;
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (i < 5)
			data->gun[i]->instances->x = data->width - data->gun[i]->width;
		if (i < 5)
			data->gun[i]->instances->y = data->height - data->gun[i]->height;
		data->portal_gun[i]->instances->x = data->width - data->portal_gun[i]->width;
		data->portal_gun[i]->instances->y = data->height - data->portal_gun[i]->height;
		i++;
	}
}

/**
 * @brief Handles the resize of the window.
 * 
 * @param width new width of the window
 * @param height new height of the window
 * @param gdata structure with all program data
 */
void	resize_window(int32_t width, int32_t height, void *gdata)
{
	t_data	*data;

	data = gdata;
	data->width = width;
	data->height = height;
	resize_render(data);
}
