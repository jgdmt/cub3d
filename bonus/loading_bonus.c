/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:23:45 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/18 15:06:29 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Enable and disable display of loading screen 
 * in function of t_data::exit value.
 * 
 * @param data structure with all program data
 */
void	loading_screen(t_data *data)
{
	static int	exit = 0;
	int			i;

	if (data->exit == 2 && exit != 2)
	{
		i = 0;
		data->loading->enabled = true;
		data->img->enabled = false;
		exit = 2;
	}
	else if (data->exit != 2 && exit == 2)
	{
		exit = 0;
		data->loading->enabled = false;
		data->img->enabled = true;
	}
}

void	cursor_screen(t_data *data)
{
	static int	i = 0;
	int			curr;

	if (data->exit)
	{
		data->cursor[i]->enabled = false;
		return ;
	}
	if (data->inv == 1)
		curr = 4;
	else if (!data->player->portal[0].status && !data->player->portal[1].status)
		curr = 0;
	else if (data->player->portal[0].status && data->player->portal[1].status)
		curr = 1;
	else if (data->player->portal[0].status)
		curr = 2;
	else
		curr = 3;
	// printf("cursor %i %i %i %i %i %i\n", curr, data->cursor[0]->enabled, data->cursor[1]->enabled, data->cursor[2]->enabled, data->cursor[3]->enabled, data->cursor[4]->enabled);
	data->cursor[i]->enabled = false;
	data->cursor[curr]->enabled = true;
	i = curr;
}
