/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:32:45 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/30 13:05:09 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	init_portal(t_portal *portal)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		portal[i].status = 0;
		portal[i].pos.x = 0;
		portal[i].pos.y = 0;
		portal[i].dir.x = 0;
		portal[i].dir.y = 0;
		i++;
	}
}

/**
 * @brief create a default config player.
 * 
 * @return t_player Initialized t_player
 */
t_player	init_player(void)
{
	t_player	player;

	player.pos.x = 0;
	player.pos.y = 0;
	player.posz = 0;
	player.nb = 0;
	player.dir.x = -1;
	player.dir.y = 0;
	player.plane.x = 0;
	player.plane.y = 1;
	player.pitch = 0;
	player.vx = 0;
	player.vy = 0;
	player.hp = 100;
	init_portal(player.portal);
	return (player);
}
