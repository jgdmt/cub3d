/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:37:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/29 14:43:42 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief The pixels buffer from the the mlx's images use ABGR but 
 * the mlx_pixel_put() function uses RGBA.
 * 
 * @param pixel a pointer at the beginning of a pixel inside 
 * the mlx_image_t::pixels
 * @return int that represent RGBA value
 */
int	correct_color(u_int8_t *pixel)
{
	int	rgba;

	rgba = 0;
	rgba += pixel[0] << 24;
	rgba += pixel[1] << 16;
	rgba += pixel[2] << 8;
	rgba += pixel[3];
	return (rgba);
}

/**
 * @brief Takes 3 vectors a rotate the first by the angle of the two others.
 * The angle between p1 and p2 need to be a multiple of 90(180, 360).
 * 
 * @param v1 the vector to be rotated
 * @param p1 the first reference vector
 * @param p2 the second reference vector
 */
void	rotate_vector(t_vector *v1, t_int_vector *p1, t_int_vector *p2)
{
	t_vector	temp;

	if (p1->x == p2->x && p1->y == p2->y)
	{
		v1->x = -v1->x;
		v1->y = -v1->y;
	}
	else if (p2->x == p1->y && p2->y == -p1->x)
	{
		temp = *v1;
		v1->x = -temp.y;
		v1->y = temp.x;
	}
	else if (p2->x == -p1->y && p2->y == p1->x)
	{
		temp = *v1;
		v1->x = temp.y;
		v1->y = -temp.x;
	}
}

/**
 * @brief Copy the whole t_data::buff inside t_data::img for 
 * refresh onscreen image.
 * 
 * @param data structure with all program data
 */
void	put_to_screen(t_data *data)
{
	int			x;
	int			width;
	int			max;
	uint32_t	*buff;

	width = data->width;
	x = 0;
	buff = data->buff;
	max = width * data ->height;
	while (x < max)
	{
		mlx_put_pixel(data->img, x - ((x % width) * width), x % width, buff[x]);
		++x;
	}
}

/**
 * @brief Puts RGBA pixel inside t_data::buff for a usage later.
 * 
 * @param data structure with all program data
 * @param x coordonate of the pixel inside the buffer
 * @param y coordonate of the pixel inside the buffer
 * @param color RGBA value store in int for the pixel
 */
void	my_mlx_put_pixel(t_data *data, int x, int y, uint32_t color)
{
	if (y < data->height && x < data->width && x >= 0 && y >= 0)
		if (color)
			data->buff[(y * data->width) + x] = color;
}

/**
 * @brief Set the rc::t pointer to the correct wall texture.
 * It selects the texture from t_data::maps textures in function
 *  of cardinal orientation.
 * 
 * @param data structure with all program data
 * @param rc structure that store all raycast parameters
 */
void	get_tex_ptr(t_data *data, t_raycast *rc)
{
	if (rc->ipos.x >= rc->player.pos.x && rc->side == 0)
		rc->t = data->map->ea;
	if (rc->ipos.x < rc->player.pos.x && rc->side == 0)
		rc->t = data->map->we;
	if (rc->ipos.y >= rc->player.pos.y && rc->side == 1)
		rc->t = data->map->no;
	if (rc->ipos.y < rc->player.pos.y && rc->side == 1)
		rc->t = data->map->so;
	if (rc->ipos.y == rc->player.portal[0].pos.y && rc->ipos.x == rc->player.portal[0].pos.x && ((rc->player.portal[0].dir.x && rc->player.portal[0].dir.x * rc->ray_dir.x < 0 && rc->side == 0) || (rc->player.portal[0].dir.y && rc->player.portal[0].dir.y * rc->ray_dir.y < 0 && rc->side == 1)))
		rc->t = data->portal[0];
	if (rc->ipos.y == rc->player.portal[1].pos.y && rc->ipos.x == rc->player.portal[1].pos.x && ((rc->player.portal[1].dir.x && rc->player.portal[1].dir.x * rc->ray_dir.x < 0 && rc->side == 0) || (rc->player.portal[1].dir.y && rc->player.portal[1].dir.y * rc->ray_dir.y < 0 && rc->side == 1)))
		rc->t = data->portal[1];
	if (data->map->map[rc->ipos.y][rc->ipos.x] == '2')
	{
		if (data->map->door_stat == 0)
			rc->t = data->map->door_open;
		else
			rc->t = data->map->door_close;
	}
}
