/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_menu_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:19:34 by jgoudema          #+#    #+#             */
/*   Updated: 2024/05/06 16:14:36 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	change_menu_text(t_data *data, int i, int j)
{
	if (i == j || i == -1)
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

void	hide_hud(t_data *data, int hidden)
{
	int	i;

	i = 0;
	data->hud.img->instances[0].enabled = hidden;
	while (i < 5)
	{
		data->cursor[i]->instances[0].enabled = hidden;
		i++;
	}
}

void	change_hud(t_data *data)
{
	if (!data->hud.hidden)
	{
		hide_hud(data, 0);
		data->hud.menu[9]->enabled = false;
		data->hud.menu[11]->enabled = true;
		data->hud.hidden = 1;
	}
	else
	{
		hide_hud(data, 1);
		data->hud.menu[11]->enabled = false;
		data->hud.menu[9]->enabled = true;
		data->hud.hidden = 0;
	}
}

int	menu_action(t_data *data, int i)
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
		show_menu(data, 0);
	if (i != 3)
		return (-1);
	return (i);
}

void	menu_events(mlx_key_data_t key, void *gdata)
{
	t_data		*data;
	static int	i = 0;
	int			old;

	data = gdata;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
	{
		menu(data);
		i = 0;
	}
	if (data->exit != MENU)
		return ;
	old = i;
	if (key.key == MLX_KEY_DOWN && key.action == MLX_PRESS)
		i = (i + 1) % 5;
	else if (key.key == MLX_KEY_UP && key.action == MLX_PRESS)
		i = (5 + i - 1) % 5;
	else if (key.key == MLX_KEY_ENTER && key.action == MLX_PRESS)
		i = menu_action(data, i);
	change_menu_text(data, i, old);
}
