/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_menu_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:19:34 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/22 21:23:12 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	change_menu_text(t_data *data, int i)
{
	(void) data;
	(void)i;
}

void	menu_events(mlx_key_data_t key, void *gdata)
{
	t_data		*data;
	static int	i = 0;
	static int	debug = 0;

	data = gdata;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
	{
		menu(data);
		i = 0;
		debug = i;
	}
	if (data->exit != 1)
		return ;
	if (key.key == MLX_KEY_DOWN && key.action == MLX_PRESS) //mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		i = (i + 1) % 4; // 5 si stats
	else if (key.key == MLX_KEY_UP && key.action == MLX_PRESS)//mlx_is_key_down(data->mlx, MLX_KEY_UP))
		i = (4 + i - 1) % 4; // 5 si stats
	else if (key.key == MLX_KEY_ENTER && key.action == MLX_PRESS) // mlx_is_key_down(data->mlx, MLX_KEY_ENTER)
	{
		if (i == 0)
			change_map(data, 1);
		else if (i == 1)
			change_map(data, -1);
		else if (i == 2)
			change_map(data, 0);
		else if (i == 3)
			free_all(MSG_GAMEQUIT, 1, data);
		i = 0;
	}
	// else
	// 	return ;
	change_menu_text(data, i);
	if (debug != i)
	{
		printf("current touch is %i ", i);
		if (i == 0)
			printf("(next map)\n");
		else if (i == 1)
			printf("(prev map)\n");
		else if (i == 2)
			printf("(reset map)\n");
		else if (i == 3)
			printf("(exit game)\n");
	}
	debug = i;
}
