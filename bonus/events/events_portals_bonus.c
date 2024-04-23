/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_portals_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:08:41 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/23 19:16:06 by jgoudema         ###   ########.fr       */
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
	init_ray_param(data->width, rc);
	step_init(rc);
	dda(data, rc, 40);
}

// void	find_xy(t_data *data, t_raycast rc, int *x, int *y)
// {
// 	if (rc.side == 0)
// 	{
// 		if (rc.x < data->player->pos.x)
// 			x = 1;
// 		else
// 			x = -1;
// 	}
// 	if (rc.side == 1)
// 	{
// 		y = -data->player->dir.y / fabs(data->player->dir.y);
// 	}
// 	return (0);
// }

/**
 * @brief Creates the portal when shot.
 * 
 * @param data structure with all program data
 * @param type portal blue or portal orange
 */
void	shoot_portal(t_data *data, int type)
{
	t_raycast	rc;
	int		other;
	int		x;
	int		y;

	get_ray(data, &rc);
	x = 0;
	y = 0;
	other = (type + 1) % 2;
	if (rc.side == 0)
	{
		x = 1;
		if (rc.ipos.x > data->player->pos.x)
			x = -1;
	}
	else
		y = -data->player->dir.y / fabs(data->player->dir.y);
	data->player->portal[type].pos.x = rc.ipos.x;
	data->player->portal[type].pos.y = rc.ipos.y;
	data->player->portal[type].dir.x = x;
	data->player->portal[type].dir.y = y;
	if (data->player->portal[other].status && data->player->portal[other].dir.x == data->player->portal[type].dir.x
		&& data->player->portal[other].dir.y == data->player->portal[type].dir.y
		&& data->player->portal[other].pos.x == data->player->portal[type].pos.x
		&& data->player->portal[other].pos.y == data->player->portal[type].pos.y)
		return ;
	if (data->player->portal[type].status == 0)
		data->player->portal[type].status = 1;

	printf("player pos %f %f, dir %f %f\n", data->player->pos.x, data->player->pos.y,
	data->player->dir.x, data->player->dir.y);
	printf("portal pos %d %d, dir %d %d\n", data->player->portal[type].pos.x, data->player->portal[type].pos.y,
	data->player->portal[type].dir.x, data->player->portal[type].dir.y);
}

/**
 * @brief Used when the player goes through a portal.
 * 
 * @param data structure with all program data
 * @param to destination portal
 */
void	tp(t_data *data, int to)
{
	int			from;
	t_vector	test;
	double		test_a;

	from = (to + 1) % 2;

	test.x = 0;
	test.y = 0;
	if (data->player->portal[from].dir.y)
		test.x = data->player->pos.x - data->player->portal[from].pos.x;
	if (data->player->portal[from].dir.x)
		test.y = data->player->pos.y - data->player->portal[from].pos.y;
	if ((data->player->portal[from].dir.x == data->player->portal[to].dir.x && data->player->portal[from].dir.y == data->player->portal[to].dir.y)
	|| (data->player->portal[from].dir.x == - data->player->portal[to].dir.y && data->player->portal[from].dir.y == - data->player->portal[to].dir.x))
	{
		if (test.x)
			test.x = 1 - test.x;
		if (test.y)
			test.y = 1 - test.y;
	}
	if (!((test.x < 0.9 && test.x > 0.1) || (test.y < 0.9 && test.y > 0.1)))
		return ;
	printf("%lf %lf\n", test.x, test.y);
	if (abs(data->player->portal[to].dir.x) != abs(data->player->portal[from].dir.x))
	{
		if (data->player->portal[to].dir.x < 0 || data->player->portal[to].dir.y < 0)
			test_a = 0.1;
		else
			test_a = 1;
			data->player->pos.x = test.y + data->player->portal[to].pos.x + data->player->portal[to].dir.x * test_a;
			data->player->pos.y = test.x + data->player->portal[to].pos.y + data->player->portal[to].dir.y * test_a;
	}
	else
	{
		if (data->player->portal[to].dir.x < 0 || data->player->portal[to].dir.y < 0)
			test_a = 0.1;
		else
			test_a = 1;
		data->player->pos.x = test.x + data->player->portal[to].pos.x + test_a * data->player->portal[to].dir.x;
		data->player->pos.y = test.y + data->player->portal[to].pos.y + test_a * data->player->portal[to].dir.y;
		printf("pos is now %lf %lf\n", data->player->pos.x, data->player->pos.y);
	}
	rotate_vector(&data->player->dir, &data->player->portal[(to + 1) % 2].dir, &data->player->portal[to].dir);
	rotate_vector(&data->player->plane, &data->player->portal[(to + 1) % 2].dir, &data->player->portal[to].dir);
}

/**
 * @brief Checks if the player goes through a portal or through the door.
 * 
 * @param data structure with all program data
 * @param x coordonate x of the future player position
 * @param y coordonate y of the future player position
 * @return int 
 */
int	check_portal(t_data *data, int x, int y, t_vector v)
{
	t_portal	*port;
	int			i;

	port = data->player->portal;
	i = 0;
	// printf("Going to %i %i\n", x, y);
	if (data->map->door_stat == 1 && ((data->map->door_pos.y == y
		&& (fabs(data->map->door_pos.x - x) == 1)) || (data->map->door_pos.x == x
		&& (fabs(data->map->door_pos.y - y) == 1))))
	{
		data->exit = 3;
		return (1);
	}
	while (i < 2)
	{
		if (port[i].status && ((port[i].pos.y == y && (abs(port[i].pos.x - x) == 1))
			|| (port[i].pos.x == x && (abs(port[i].pos.y - y) == 1))))
			if (port[(i + 1) % 2].status)
				if ((port[i].dir.x && port[i].dir.x * v.x < 0) || (port[i].dir.y && port[i].dir.y * v.y < 0))
					return (tp(data, (i + 1) % 2), 1);
		i++;
	}
	return (0);
}

/**
 * @brief Resets the portals.
 * 
 * @param data structure with all program data
 */
void	reset_portal(t_data *data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		data->player->portal[i].status = 0;
		data->player->portal[i].pos.y = 0;
		data->player->portal[i].pos.x = 0;
		data->player->portal[i].dir.x = 0;
		data->player->portal[i].dir.y = 0;
		i++;
	}
}
