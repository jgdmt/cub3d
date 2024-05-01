/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:09:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/01 15:42:59 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_map		map;
	t_data		data;
	t_player	player;
	mlx_t		*mlx;
	pthread_t	thread;
	pthread_t	inertia;
	pthread_t	hud;

	if (argc < 2 || argc > 11)
		return (ft_printf(2, ERR_ARGV), 0);
	mlx = mlx_init(WIDTH, HEIGHT, "🐺Cub3D 🐉🐺", true);
	if (!mlx)
		return (ft_printf(2, ERR_MLX), 0);
	mlx_set_window_limit(mlx, 384, 216, 3840, 2160);
	map = init_map();
	player = init_player();
	data = init_data(&map, &player, mlx, argv);
	parsing(argv[1], &data);
	data.hud_img = mlx_new_image(mlx, data.hud.width, data.hud.height);
	data.buff = malloc(WIDTH * HEIGHT * sizeof(int));
	if (!data.buff || !data.hud_img)
		free_all(ERR_MALLOC, 2, &data);
	if (pthread_create(&thread, NULL, raycast_threader, &data))
		free_all(ERR_MUTEX, 2, &data);
	if (pthread_create(&inertia, NULL, update_inertia, &data))
		free_all(ERR_MUTEX, 2, &data);
	if (pthread_create(&hud, NULL, thread_hud, &data))
		free_all(ERR_MUTEX, 2, &data);
	if (mlx_image_to_window(data.mlx, data.hud_img, 0, 0) == -1)
		free_all(ERR_MLX, 2, &data);
	printf("%i\n", data.img->instances[0].z);
	mlx_loop_hook(mlx, &hook, &data);
	mlx_resize_hook(mlx, &resize_window, &data);
	mlx_close_hook(mlx, &close_window, &data);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	mlx_mouse_hook(mlx, &portals, &data);
	mlx_scroll_hook(mlx, &scroll, &data);
	mlx_key_hook(mlx, &menu_events, &data);
	mlx_loop(mlx);
	return (0);
}
