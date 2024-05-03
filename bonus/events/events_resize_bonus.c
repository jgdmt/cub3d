/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_resize_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:36:21 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/03 20:25:16 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	repos_hud(t_data *data, mlx_image_t **cursor)
{
	int	i;
	int	j;

	i = 0;
	cursor = data->cursor;
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
}

void	init_hud(t_data *data)
{
	uint32_t	i;
	uint32_t	j;
	mlx_image_t	*img;

	i = 0;
	img = data->hud.img;
	while ((unsigned int)++i < img->height * img->width)
		img->pixels[i * 4 + 3] = 0x00;
	i = img->width / 2 - img->width / 40;
	while (i < img->width / 2 + img->width / 40)
	{
		j = img->width / 2 - img->width / 40;
		while (j < img->width / 2 + img->width / 40)
			mlx_put_pixel(img, i, j++, 0xff0000ff);
		i++;
	}
}

void	gun_hud(t_data *data)
{
	int			i;
	mlx_image_t	**pg;

	i = 0;
	pg = data->portal_gun;
	while (i < 10)
	{
		if (i < 5)
			data->gun[i]->instances->x = data->width - data->gun[i]->width;
		if (i < 5)
			data->gun[i]->instances->y = data->height - data->gun[i]->height;
		pg[i]->instances->x = data->width - pg[i]->width;
		pg[i]->instances->y = data->height - pg[i]->height;
		i++;
	}
}

/**
 * @brief Detect a change in width and height from struct data in comparaison
 * with last call a recreate the data->img(mlx_image_t *).
 * If this function encounter a problem they stop the programm with free_all().
 * 
 * @param data structure with all program data
 */
void	resize_render(t_data *data)
{
	bool		check[2];

	free(data->buff);
	free(data->hud.buff);
	check[0] = mlx_resize_image(data->img, data->width, data->height);
	check[1] = mlx_resize_image(data->hud.img, data->height / 3, \
	data->height / 3 + 15);
	data->buff = malloc(data->width * data->height * sizeof(int));
	data->hud.buff = malloc(data->hud.img->width * \
	(data->hud.img->height - 15) * sizeof(uint32_t));
	if (!check[0] || !check[1] || !data->buff)
		free_all(ERR_MALLOC, 2, data);
	repos_hud(data, data->cursor);
	init_hud(data);
	gun_hud(data);
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
