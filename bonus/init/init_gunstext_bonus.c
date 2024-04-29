/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gunstext_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:32:11 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/29 15:24:16 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

char	*assets_portalgun(int i)
{
	(void) i;
	return ("./bonus/assets/portal_gun.png");
}

char	*assets_gun(int i)
{
	if (i == 0)
		return ("./bonus/assets/gun_anim/00_gun_anim.png");
	else if (i == 1)
		return ("./bonus/assets/gun_anim/01_gun_anim.png");
	else if (i == 2)
		return ("./bonus/assets/gun_anim/02_gun_anim.png");
	else if (i == 3)
		return ("./bonus/assets/gun_anim/03_gun_anim.png");
	else
		return ("./bonus/assets/gun_anim/04_gun_anim.png");
}

void	init_portalgun_text(t_data *data, mlx_t *mlx)
{
	data->portal_gun = create_image(mlx, assets_portalgun, 0);
	if (mlx_image_to_window(mlx, data->portal_gun, data->width
			- data->portal_gun->width, data->height
			- data->portal_gun->height) == -1)
		free_all(ERR_MLX, 2, data);
	data->portal_gun->instances[0].z = 25;
	data->portal_gun->enabled = false;
}

void	init_gun_text(t_data *data, mlx_t *mlx)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		data->gun[i] = create_image(mlx, assets_gun, i);
		if (!data->gun[i])
			free_all(ERR_MLX, 2, data);
		if (mlx_image_to_window(mlx, data->gun[i], data->width
				- data->gun[i]->width, data->height
				- data->gun[i]->height) == -1)
			free_all(ERR_MLX, 2, data);
		data->gun[i]->instances[0].z = 25;
		data->gun[i]->enabled = false;
		i++;
	}
}
