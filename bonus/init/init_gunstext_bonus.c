/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gunstext_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:32:11 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/29 19:03:58 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

char	*assets_portalgun(int i)
{
	if (i == 0)
		return ("./bonus/assets/portal_gun/b_portal_gun_0.png");
	else if (i == 1)
		return ("./bonus/assets/portal_gun/b_portal_gun_1.png");
	else if (i == 2)
		return ("./bonus/assets/portal_gun/b_portal_gun_2.png");
	else if (i == 3)
		return ("./bonus/assets/portal_gun/b_portal_gun_3.png");
	else if (i == 4)
		return ("./bonus/assets/portal_gun/b_portal_gun_4.png");
	else if (i == 5)
		return ("./bonus/assets/portal_gun/o_portal_gun_0.png");
	else if (i == 6)
		return ("./bonus/assets/portal_gun/o_portal_gun_1.png");
	else if (i == 7)
		return ("./bonus/assets/portal_gun/o_portal_gun_2.png");
	else if (i == 8)
		return ("./bonus/assets/portal_gun/o_portal_gun_3.png");
	else
		return ("./bonus/assets/portal_gun/o_portal_gun_4.png");
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
	int	i;

	i = 0;
	while (i < 10)
	{
		data->portal_gun[i] = create_image(mlx, assets_portalgun, i);
		if (mlx_image_to_window(mlx, data->portal_gun[i], data->width
				- data->portal_gun[i]->width, data->height
				- data->portal_gun[i]->height) == -1)
			free_all(ERR_MLX, 2, data);
		data->portal_gun[i]->instances[0].z = 34;
		data->portal_gun[i]->enabled = false;
		i++;
	}
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
		data->gun[i]->instances[0].z = 34;
		data->gun[i]->enabled = false;
		i++;
	}
}
