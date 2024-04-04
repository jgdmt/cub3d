/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_portal_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:10:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/04 19:47:22 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	portal(t_data *data, t_raycast *rc)
{
	printf("test\n");
	// if (rc->side == 0)
	// 	rc->portal_first_ray = (rc->side_dist.x - rc->delta_dist.x);
	// else
	// 	rc->portal_first_ray = (rc->side_dist.y - rc->delta_dist.y);
	init_ray_param(data->width, rc);
	step_init(rc);
	dda(data, rc);
}
