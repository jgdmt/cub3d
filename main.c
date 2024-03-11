/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:09:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/03/11 12:58:53 by jgoudema         ###   ########.fr       */
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
	map.floor_color = 0;
	map.ceiling_color = 0;
	return (map);
}

t_data	init_data(t_map *map)
{
	t_data	data;

	data.player = 0;
	data.map_data = map;
	return (data);
}

int	main(int argc, char **argv)
{
	t_map		map_data;
	t_data		data;

	if (argc != 2)
		return (ft_printf(2, "Error: wrong number of arguments."), 0);
	map_data = init_map();
	data = init_data(&map_data);
	parsing(argv[1], &data);
	(void) argc;
	(void) argv;
	// raycast_test();
	return (0);
}
