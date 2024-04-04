/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:09:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/04 21:39:24 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	map.max = 0;
	map.maxy = 0;
	map.enemies = 0;
	map.door.pos.x = 0;
	map.door.pos.y = 0;
	map.door.status = -1;
	return (map);
}

void	init_portal(t_portal *portal)
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

t_player	init_player(void)
{
	t_player	player;

	player.pos.x = 0;
	player.pos.y = 0;
	player.nb = 0;
	player.dir.x = -1;
	player.dir.y = 0;
	player.plane.x = 0;
	player.plane.y = 1;
	player.pitch = 0;
	init_portal(player.portal);
	return (player);
}

t_data	init_data(t_map *map, t_player *player, mlx_t *mlx, char **argv)
{
	t_data			data;
	mlx_texture_t	*loading;

	data.player = player;
	data.map = map;
	data.mlx = mlx;
	data.width = WIDTH;
	data.height = HEIGHT;
	data.img = 0;
	data.exit = 0;
	data.inv = 0;
	data.loading = 0;
	data.argv = argv;
	if (pthread_mutex_init(&data.lock, NULL) != 0)
		free_all(ERR_MUTEX, 2, &data);
	loading = mlx_load_png("./bonus/assets/icon.png");
	if (!loading)
		free_all(ERR_MLX, 2, &data);
	data.loading = mlx_texture_to_image(data.mlx, loading);
	mlx_delete_texture(loading);
	if (!data.loading)
		free_all(ERR_MLX, 2, &data);
	if (mlx_image_to_window(data.mlx, data.loading, 704, 284) == -1)
		free_all(ERR_MLX, 2, &data);
	data.loading->enabled = false;
	return (data);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_data		data;
	t_player	player;
	mlx_t		*mlx;
	pthread_t	thread;

	if (argc < 2 || argc > 11)
		return (ft_printf(2, ERR_ARGV), 0);
	mlx = mlx_init(WIDTH, HEIGHT, "🐺Cub3D 🐉🐺", true);
	if (!mlx)
		return (ft_printf(2, ERR_MLX), 0);
	map = init_map();
	player = init_player();
	data = init_data(&map, &player, mlx, argv);
	parsing(argv[1], &data);
	data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	data.buff = malloc(WIDTH * HEIGHT * sizeof(int));
	if (!data.img || !data.buff)
		free_all(ERR_MALLOC, 2, &data);
	if (pthread_create(&thread, NULL, raycast_threader, &data))
		free_all(ERR_MUTEX, 2, &data);
	// raycast(&data);
	if (mlx_image_to_window(data.mlx, data.img, 0, 0) == -1)
		free_all(ERR_MLX, 2, &data);
	// mlx_key_hook(mlx, &keypress, &data);
	mlx_loop_hook(mlx, &hook, &data);
	mlx_resize_hook(mlx, &resize_window, &data);
	mlx_close_hook(mlx, &close_window, &data);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	mlx_mouse_hook(mlx, &portals, &data);
	mlx_scroll_hook(mlx, &scroll, &data);
	mlx_loop(mlx);
	return (0);
}
