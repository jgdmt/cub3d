/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:09:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/03/12 17:42:07 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	init_map(void)
{
	t_map	map;

	map.map = 0;
	map.no_texture = 0;
	map.so_texture = 0;
	map.we_texture = 0;
	map.ea_texture = 0;
	map.floor_color = -1;
	map.ceiling_color = -1;
	return (map);
}
t_player	init_player(void)
{
	t_player	player;

	player.direction = 0;
	player.x = 0;
	player.y = -1;
	player.nb = 0;
	return (player);
}

t_data	init_data(t_map *map, t_player *player)
{
	t_data	data;

	data.player = player;
	data.map_data = map;
	return (data);
}


int	main(int argc, char **argv)
{
	t_map		map_data;
	t_data		data;
	t_player	player;

	if (argc != 2)
		return (ft_printf(2, ERR_ARGV), 0);
	map_data = init_map();
	player = init_player();
	data = init_data(&map_data, &player);
	parsing(argv[1], &data);
	raycast_test();
	free_all(0, 0, &map_data);
	return (0);
}
