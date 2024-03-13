/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:09:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/03/13 16:14:18 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	init_map(void)
{
	t_map	map;

	map.map = 0;
	map.no = 0;
	map.so = 0;
	map.we = 0;
	map.ea = 0;
	map.floor_color = -1;
	map.ceiling_color = -1;
	return (map);
}

t_player	init_player(void)
{
	t_player	player;

	player.direction = 0;
	player.pos.x = 0;
	player.pos.y = 0;
	player.nb = 0;
	return (player);
}

t_data	init_data(t_map *map, t_player *player, mlx_t *mlx)
{
	t_data	data;

	data.player = player;
	data.map = map;
	data.mlx = mlx;
	return (data);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_data		data;
	t_player	player;
	mlx_t		*mlx;

	if (argc != 2)
		return (ft_printf(2, ERR_ARGV), 0);
	mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
		return (ft_printf(2, ERR_MLX), 0);
	map = init_map();
	player = init_player();
	data = init_data(&map, &player, mlx);
	parsing(argv[1], &data);
	// mlx_image_to_window(mlx, map.no, 0, 0);
	data.img = mlx_new_image(mlx, 1920, 1080);
	raycast(&data);
	mlx_key_hook(mlx, &keypress, &data);
	mlx_close_hook(mlx, &close_window, &data);
	mlx_loop(mlx);
	// mlx_terminate(mlx);
	// raycast_test();
	// free_all(0, 0, &data);
	return (0);
}
