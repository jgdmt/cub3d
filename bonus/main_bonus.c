/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:09:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/06 15:14:12 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	door(mlx_key_data_t key, void *gdata)
{
	t_data	*data;

	data = gdata;
	if (key.key == MLX_KEY_E && key.action == MLX_PRESS)
		door_event(data);
}

void	key_events(mlx_key_data_t key, void *gdata)
{
	menu_events(key, gdata);
	door(key, gdata);
}

void	play(t_data *data)
{
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_resize_hook(data->mlx, &resize_window, data);
	mlx_close_hook(data->mlx, &close_window, data);
	mlx_mouse_hook(data->mlx, &portals, data);
	mlx_scroll_hook(data->mlx, &scroll, data);
	mlx_key_hook(data->mlx, &key_events, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_data		data;
	t_player	player;
	mlx_t		*mlx;

	if (argc < 2 || argc > 11)
		return (ft_printf(2, ERR_ARGV), 0);
	mlx = mlx_init(WIDTH, HEIGHT, "🐺Cub3D 🐉🐺", true);
	if (!mlx)
		return (ft_printf(2, ERR_MLX), 0);
	mlx_set_window_limit(mlx, 1285, 800, 3840, 2160);
	map = init_map();
	player = init_player();
	data = init_data(&map, &player, mlx, argv);
	parsing(argv[1], &data);
	data.buff = malloc(WIDTH * HEIGHT * sizeof(int));
	if (!data.buff)
		free_all(ERR_MALLOC, 2, &data);
	init_thread(&data);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	play(&data);
	return (0);
}
