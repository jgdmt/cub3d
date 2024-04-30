/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:31:33 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/30 16:20:16 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

t_map	init_map(void)
{
	t_map	map;

	map.map = 0;
	map.no = 0;
	map.so = 0;
	map.we = 0;
	map.ea = 0;
	map.floor_color = 0;
	map.ceiling_color = 0;
	map.en_sprites = 0;
	map.max = 0;
	map.maxy = 0;
	map.enemies = 0;
	map.nb_enemy = 0;
	map.door_pos.x = 0;
	map.door_pos.y = 0;
	map.door_stat = -1;
	map.sp_distance = 0;
	map.sp_order = 0;
	return (map);
}
