/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_tp_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:55:15 by jgoudema          #+#    #+#             */
/*   Updated: 2024/05/07 17:13:08 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	tp_get_test(t_data *data, int to, int from, t_vector *test)
{
	test->x = 0;
	test->y = 0;
	if (data->player->portal[from].dir.y)
		test->x = data->player->pos.x - data->player->portal[from].pos.x;
	if (data->player->portal[from].dir.x)
		test->y = data->player->pos.y - data->player->portal[from].pos.y;
	if ((data->player->portal[from].dir.x == data->player->portal[to].dir.x \
		&& data->player->portal[from].dir.y == data->player->portal[to].dir.y) \
		|| (data->player->portal[from].dir.x == -data->player->portal[to].dir.y \
		&& data->player->portal[from].dir.y == -data->player->portal[to].dir.x))
	{
		if (test->x)
			test->x = 1 - test->x;
		if (test->y)
			test->y = 1 - test->y;
	}
}

/**
 * @brief Used when the player goes through a portal.
 * 
 * @param data structure with all program data
 * @param to destination portal
 */
void	tp(t_data *data, int to, int from)
{
	t_vector	test;
	t_player	*p;
	double		test_a;
	double		tmp;

	tp_get_test(data, to, from, &test);
	p = data->player;
	if (!((test.x < 0.9 && test.x > 0.1) || (test.y < 0.9 && test.y > 0.1)))
		return ;
	if (p->portal[to].dir.x < 0 || p->portal[to].dir.y < 0)
		test_a = 0.1;
	else
		test_a = 1.1;
	if (abs(p->portal[to].dir.x) != abs(p->portal[from].dir.x))
	{
		tmp = test.x;
		test.x = test.y;
		test.y = tmp;
	}
	p->pos.x = test.x + p->portal[to].pos.x + test_a * p->portal[to].dir.x;
	p->pos.y = test.y + p->portal[to].pos.y + test_a * p->portal[to].dir.y;
	rot_vector(&p->dir, &p->portal[(to + 1) % 2].dir, &p->portal[to].dir);
	rot_vector(&p->plane, &p->portal[(to + 1) % 2].dir, &p->portal[to].dir);
}
