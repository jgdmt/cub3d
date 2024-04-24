/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_menu_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:19:34 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/24 16:28:57 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	change_menu_text(t_data *data, int i, int j)
{
	if (i == j)
		return ;
	if (j == 3 && data->hud.hidden)
		j = 5;
	data->hud.menu[j + 6]->enabled = false;
	data->hud.menu[j]->enabled = true;
	if (i == 3 && data->hud.hidden)
		i = 5;
	data->hud.menu[i + 6]->enabled = true;
	data->hud.menu[i]->enabled = false;
}

void	change_hud(t_data *data)
{
	if (!data->hud.hidden)
	{
		data->img->instances[0].z = 19;
		data->hud_img->instances[0].z = 22;
		data->hud.menu[9]->enabled = false;
		data->hud.menu[11]->enabled = true;
		data->hud.hidden = 1;
	}
	else
	{
		data->img->instances[0].z = 18;
		data->hud_img->instances[0].z = 7;
		data->hud.menu[11]->enabled = false;
		data->hud.menu[9]->enabled = true;
		data->hud.hidden = 0;
	}
}

void	menu_events(mlx_key_data_t key, void *gdata)
{
	t_data		*data;
	static int	i = 0;
	int			old;
	// static int	debug = 0;

	data = gdata;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
	{
		menu(data);
		i = 0;
		// debug = i;
	}
	if (data->exit != 1)
		return ;
	old = i;
	if (key.key == MLX_KEY_DOWN && key.action == MLX_PRESS) //mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		i = (i + 1) % 5; // 6 si stats
	else if (key.key == MLX_KEY_UP && key.action == MLX_PRESS)//mlx_is_key_down(data->mlx, MLX_KEY_UP))
		i = (5 + i - 1) % 5; // 6 si stats
	else if (key.key == MLX_KEY_ENTER && key.action == MLX_PRESS) // mlx_is_key_down(data->mlx, MLX_KEY_ENTER)
	{
		if (i == 0)
			change_map(data, 1);
		else if (i == 1)
			change_map(data, -1);
		else if (i == 2)
			change_map(data, 0);
		else if (i == 3)
			change_hud(data);
		else if (i == 4)
			free_all(MSG_GAMEQUIT, 1, data);
		if (i != 3)
			i = 0;
	}
	change_menu_text(data, i, old);
	// else
	// 	return ;
	// if (debug != i)
	// {
	// 	printf("current touch is %i ", i);
	// 	if (i == 0)
	// 		printf("(next map)\n");
	// 	else if (i == 1)
	// 		printf("(prev map)\n");
	// 	else if (i == 2)
	// 		printf("(reset map)\n");
	// 	else if (i == 3)
	// 		printf("(hide/show hud)\n");
	// 	else if (i == 4)
	// 		printf("(exit game)\n");
	// }
	// debug = i;
}
