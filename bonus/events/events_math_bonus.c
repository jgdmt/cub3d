/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_math_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:40:05 by jgoudema          #+#    #+#             */
/*   Updated: 2024/05/03 18:53:54 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief Get the ray object
 * 
 * @param data structure with all program data
 * @param rc ray
 */
void	get_ray(t_data *data, t_raycast *rc)
{
	rc->player = *(data->player);
	rc->x = data->width / 2;
	rc->player.plane.x = 0;
	rc->player.plane.y = 0;
	cast_a_ray(data, rc, 40);
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
