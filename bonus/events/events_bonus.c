/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:10:19 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/23 19:03:56 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	mouse_move(void *gdata);
int		check_portal(t_data *data, int x, int y, t_vector v);

void	door_event(t_data *data)
{
	printf("%f %f %f %f\n", data->map->door_pos.x, data->map->door_pos.y, data->player->pos.x, data->player->pos.y);
	if (fabs(data->player->pos.x - data->map->door_pos.x) < 2.5
		&& fabs(data->player->pos.y - data->map->door_pos.y) < 2.5)
	{
		if (data->map->door_stat)
			data->map->door_stat = 0;
		else
			data->map->door_stat = 1;
		ft_usleep(250);
	}
}

/**
 * @brief Allows the player to rotate.
 * 
 * @param speed speed of the rotation
 * @param data structure with all program data
 */
void	rotate(double speed, t_data *data)
{
	double	old_x;
	double	old_y;

	old_x = data->player->dir.x;
	old_y = data->player->dir.y;
	data->player->dir.x = old_x * cos(speed) - old_y * sin(speed);
	data->player->dir.y = old_x * sin(speed) + old_y * cos(speed);
	old_x = data->player->plane.x;
	old_y = data->player->plane.y;
	data->player->plane.x = old_x * cos(speed) - old_y * sin(speed);
	data->player->plane.y = old_x * sin(speed) + old_y * cos(speed);
}

/**
 * @brief Finds the angle between two vectors. The angle is always the same
 * and might not be the smallest.
 * 
 * @param ux value x of the vector u
 * @param uy value y of the vector u
 * @param vx value x of the vector v
 * @param vy value y of the vector v
 * @return float 
 */
float	angle(double ux, double uy, double vx, double vy)
{
	float	ps;
	float	u_norm;
	float	v_norm;

	ps = ux * vx + uy * vy;
	u_norm = sqrt(pow(ux, 2) + pow(uy, 2));
	v_norm = sqrt(pow(ux, 2) + pow(uy, 2));
	if (ux > 0)
		return (acos(ps / (u_norm * v_norm)));
	else
		return (-acos(ps / (u_norm * v_norm)));
}

/**
 * @brief Allows the player to move.
 * 
 * @param data structure with all program data
 */
void	move(t_data *data)
{
	int			sign;
	t_vector	pos;
	char		**map;
	t_vector	v;
	float		theta;

	sign = 0;
	if (data->player->vx < 10e-7 && data->player->vx > -10e-7 && data->player->vy < 10e-7 && data->player->vy > -10e-7)
		return ;
	theta = angle(data->player->dir.x, data->player->dir.y, 0, -1);
	v.x = data->player->vx * cos(theta) + data->player->vy * - sin(theta);
	v.y = data->player->vx * sin(theta) + data->player->vy * cos(theta);
	map = data->map->map;
	pos = data->player->pos;
	// printf("%f\n", theta);
	if (fabs(v.x) == 1)
		sign = v.x;
	if (map[(int)(pos.y + sign * 0.1)][(int)(pos.x + v.x * 2)] == '0'
		&& map[(int)(pos.y - sign * 0.1)][(int)(pos.x + v.x * 2)] == '0')
		data->player->pos.x += v.x;
	else
	{
		if (check_portal(data, floor(pos.x + v.x), floor(pos.y), v))
			return ;
		else
			data->player->vx = 0;
	}
	if (fabs(v.y) == 1)
		sign = v.y;
	if (map[(int)(pos.y + v.y * 2)][(int)(pos.x + sign * 0.1)] == '0'
		&& map[(int)(pos.y + v.y * 2)][(int)(pos.x - sign * 0.1)] == '0')
		data->player->pos.y += v.y;
	else
	{
		if (check_portal(data, floor(pos.x), floor(pos.y + v.y), v))
			return ;
		else
			data->player->vy = 0;
	}
}

/**
 * @brief Handles the possible inputs.
 * 
 * @param gdata structure with all program data
 */
void	hook(void *gdata)
{
	t_data			*data;
	static int		i = 0;

	data = gdata;
	if (i < 2)
	{
		mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
		i++;
	}
	// if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	// 	menu(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q) && data->exit == 1)
		free_all("Game quit", 1, data);
	// if (data->exit == 1)
	// 	menu_events(data);
	if (data->exit == 3)
		change_map(data, 1);
	if (data->exit)
		return ;
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		door_event(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate(RSPEED, data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate(-RSPEED, data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) && data->player->vy > -MAXV)
		data->player->vy -= ACCELERATION;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) && data->player->vy < MAXV)
		data->player->vy += ACCELERATION;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) && data->player->vx < MAXV)
		data->player->vx += ACCELERATION;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D) && data->player->vx > -MAXV)
		data->player->vx -= ACCELERATION;
	// if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	// 	jump(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_N))
		change_map(data, 1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_P))
		change_map(data, -1);
	mouse_move(gdata);
}

/**
 * @brief Handles the closing of the window.
 * 
 * @param gdata structure with all program data
 */
void	close_window(void *gdata)
{
	t_data	*data;

	data = gdata;
	free_all("Game closed", 1, data);
}

/**
 * @brief Handles the resize of the window.
 * 
 * @param width new width of the window
 * @param height new height of the window
 * @param gdata structure with all program data
 */
void	resize_window(int32_t width, int32_t height, void *gdata)
{
	t_data	*data;

	data = gdata;
	data->width = width;
	data->height = height;
	resize_render(data);
}
