/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:23:45 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/15 20:10:04 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	loading_screen(t_data *data)
{
	static int	exit = 0;
	int	i;

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
	if (!data->player->portal[0].status && !data->player->portal[1].status)
		curr = 0;
	else if (data->player->portal[0].status && data->player->portal[1].status)
		curr = 1;
	else if (data->player->portal[0].status)
		curr = 2;
	else
		curr = 3;
	data->cursor[i]->enabled = false;
	data->cursor[curr]->enabled = true;
	i = curr;
}
