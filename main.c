/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:09:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/03/13 11:58:34 by vilibert         ###   ########.fr       */
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
	player.y = 0;
	player.nb = 0;
	return (player);
}

t_data	init_data(t_map *map, t_player *player, mlx_t *mlx)
{
	t_data	data;

	data.player = player;
	data.map_data = map;
	data.mlx = mlx;
	return (data);
}
mlx_image_t *img;

int	main(int argc, char **argv)
{
	t_map		map_data;
	t_data		data;
	t_player	player;
	mlx_t		*mlx;

	if (argc != 2)
		return (ft_printf(2, ERR_ARGV), 0);
	mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
		return (ft_printf(2, ERR_MLX), 0);
	map_data = init_map();
	player = init_player();
	data = init_data(&map_data, &player, mlx);
	parsing(argv[1], &data);
	// mlx_image_to_window(mlx, map_data.no_texture, 0, 0);
	img = mlx_new_image(mlx, 1920, 1080);
	raycast_test();
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, &keypress, &data);
	mlx_close_hook(mlx, &close_window, &data);
	mlx_loop(mlx);
	// raycast_test();
	// free_all(0, 0, &data);
	return (0);
}
