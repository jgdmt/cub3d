/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_portal_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:10:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/10 17:05:43 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	portal_0(t_data *data, t_raycast *rc)
{
	printf("test\n");
	t_raycast test;
	if (rc->side == 0)
		rc->portal_first_ray += (rc->side_dist.x - rc->delta_dist.x);
	else
		rc->portal_first_ray += (rc->side_dist.y - rc->delta_dist.y);
	test = *rc;
	test.player.pos.x = rc->player.portal[1].pos.x;
	test.player.pos.y = rc->player.portal[1].pos.y;
	test.player.dir.x = rc->player.portal[1].dir.x;
	test.player.dir.y = rc->player.portal[1].dir.y;
	init_ray_param(data->width, &test);
	step_init(&test);
	dda(data, &test);
	rc->portal_first_ray += test.portal_first_ray;
	rc->ipos = test.ipos;
}
