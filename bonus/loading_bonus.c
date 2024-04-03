/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:23:45 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/03 13:56:47 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	loading_screen(t_data *data)
{
	static int	exit = 0;

	if (data->exit == 2 && exit != 2)
	{
		data->loading->enabled = true;
		data->img->enabled = false;
		ft_usleep(1000);
		exit = 2;
	}
	else if (data->exit != 2 && exit == 2)
	{
		exit = 0;
		data->loading->enabled = false;
		data->img->enabled = true;
	}

}
