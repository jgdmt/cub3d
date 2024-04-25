/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:53:39 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/25 19:33:28 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	shoot_portal(t_data *data, int type);
void	rotate(double speed, t_data *data);
void	get_ray(t_data *data, t_raycast *rc);

/**
 * @brief Handles the scrolling and the inventory.
 * 
 * @param xdelta scrolling in x
 * @param ydelta scrolling in y
 * @param gdata structure with all program data
 */
void	scroll(double xdelta, double ydelta, void *gdata)
{
	t_data	*data;

	data = gdata;
	if (data->exit)
		return ;
	(void) xdelta;
	if (ydelta < 0)
		data->inv = (data->inv + 1) % 2;
	if (ydelta > 0)
		data->inv = (2 + data->inv - 1) % 2;
	printf("inventory slot: %i\n", data->inv);
}

double	get_speed(int32_t diff)
{
	double	speed;

	speed = RSPEED * (diff / abs(diff));
	if (abs(diff) < 2)
		return (speed / 10);
	else if (abs(diff) > 20)
		return (speed);
	else
		return (speed / (10 - abs(diff) % 10));
}

/**
 * @brief Handles the player's rotation with the mouse.
 * 
 * @param gdata structure with all program data
 */
void	mouse_move(void *gdata)
{
	static int32_t	old_x = WIDTH / 2;
	static int32_t	old_y = HEIGHT / 2;
	int32_t			x;
	int32_t			y;
	t_data			*data;

	data = gdata;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (data->exit)
	{
		old_x = x;
		old_y = y;
		return ;
	}
	if (x != old_x)
		rotate(get_speed(old_x - x), data);
	if (y < old_y && data->player->pitch < 500)
		data->player->pitch += 25;
	if (y > old_y && data->player->pitch > -500)
		data->player->pitch -= 25;
	old_x = x;
	old_y = y;
}

void	debug(t_data *data)
{
	printf("player pos %f %f, dir %f %f\n", data->player->pos.x, data->player->pos.y,
	data->player->dir.x, data->player->dir.y);
	printf("portal blue pos %d %d, dir %d %d\n", data->player->portal[BLUE].pos.x, data->player->portal[BLUE].pos.y,
	data->player->portal[BLUE].dir.x, data->player->portal[BLUE].dir.y);
	printf("portal orange pos %d %d, dir %d %d\n", data->player->portal[ORANGE].pos.x, data->player->portal[ORANGE].pos.y,
	data->player->portal[ORANGE].dir.x, data->player->portal[ORANGE].dir.y);
	int i = 0;
	while (data->map->map[i])
	{
	int j = 0;
		while (data->map->map[i][j])
		{
			if (i == floor(data->player->pos.y) && j == floor(data->player->pos.x))
				printf("\e[0;32mP\e[0;37m");
			else
			{
				if (data->map->nb_enemy > 0)
				{
					int k = 0;
					while (k < data->map->nb_enemy)
					{
						if (data->map->enemies[k].pos.x == j && data->map->enemies[k].pos.y == i)
							printf("\033[31mE\e[0;37m");
						k++;
					}
					if (k == data->map->nb_enemy)
						printf("%c", data->map->map[i][j]);
				}
				else
					printf("%c", data->map->map[i][j]);

			}
			j++;
		}
		printf("\n");
		i++;
	}
}

/**
 * @brief Handles the actions with the mouse.
 * 
 * @param button button of the mouse used
 * @param act key action
 * @param mod key modifiers
 * @param dt structure with all program data
 */
void	portals(mouse_key_t button, action_t act, modifier_key_t mod, void *dt)
{
	t_data	*data;

	(void) mod;
	data = dt;
	if (data->exit)
		return ;
	if (button == MLX_MOUSE_BUTTON_LEFT && act == MLX_PRESS && data->inv == 0)
		shoot_portal(data, BLUE);
	if (button == MLX_MOUSE_BUTTON_RIGHT && act == MLX_PRESS && data->inv == 0)
		shoot_portal(data, ORANGE);
	if (button == MLX_MOUSE_BUTTON_MIDDLE && mod == MLX_SHIFT && act == MLX_PRESS && data->inv == 0)
		debug(data);
	else if (button == MLX_MOUSE_BUTTON_MIDDLE && act == MLX_PRESS && data->inv == 0)
		reset_portal(data);
	if (button == MLX_MOUSE_BUTTON_LEFT && act == MLX_PRESS && data->inv == 1)
		shoot(data);
}
