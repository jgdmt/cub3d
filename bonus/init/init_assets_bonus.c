/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assets_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:16:39 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/26 15:42:38 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

char	*assets_portals(int i)
{
	if (i == 0)
		return ("./bonus/assets/bportal_close.png");
	else if (i == 1)
		return ("./bonus/assets/oportal_close.png");
	else if (i == 2)
		return ("./bonus/assets/bportal_open.png");
	else
		return ("./bonus/assets/oportal_open.png");
}

char	*assets_cursor(int i)
{
	if (i == 0)
		return ("./bonus/assets/empty.png");
	else if (i == 1)
		return ("./bonus/assets/full.png");
	else if (i == 2)
		return ("./bonus/assets/blue.png");
	else if (i == 3)
		return ("./bonus/assets/orange.png");
	else
		return ("./bonus/assets/aim.png");
}

char	*assets_doors(int i)
{
	if (i == 0)
		return ("./maps/pics/door_close_128.png");
	else
		return ("./maps/pics/door_open_128.png");
}

char	*assets_hud(int i)
{
	if (i == 0)
		return ("./bonus/assets/next_map.png");
	else if (i == 1)
		return ("./bonus/assets/previous_map.png");
	else if (i == 2)
		return ("./bonus/assets/reset_map.png");
	else if (i == 3)
		return ("./bonus/assets/hide_hud.png");
	else if (i == 4)
		return ("./bonus/assets/exit.png");
	else if (i == 5)
		return ("./bonus/assets/show_hud.png");
	else if (i == 6)
		return ("./bonus/assets/next_map_selected.png");
	else if (i == 7)
		return ("./bonus/assets/previous_map_selected.png");
	else if (i == 8)
		return ("./bonus/assets/reset_map_selected.png");
	else if (i == 9)
		return ("./bonus/assets/hide_hud_selected.png");
	else if (i == 10)
		return ("./bonus/assets/exit_selected.png");
	else
		return ("./bonus/assets/show_hud_selected.png");
}
