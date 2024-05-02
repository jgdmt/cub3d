/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:11:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/02 11:34:21 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	sort(t_map *map)
{
	int		i;
	double	ftemp;
	int		temp;
	int		max;
	int		j;

	i = 0;
	while (i < map->nb_enemy - 1)
	{
		j = i;
		ftemp = map->sp_distance[i];
		max = i;
		while (++j < map->nb_enemy)
		{
			if (map->sp_distance[max] < map->sp_distance[j])
				max = j;
		}
		map->sp_distance[i] = map->sp_distance[max];
		map->sp_distance[max] = ftemp;
		temp = map->sp_order[i];
		map->sp_order[i] = map->sp_order[max];
		map->sp_order[max] = temp;
		i++;
	}

}

static void	order_sprites(t_map	*map, t_raycast *rc)
{
	int	i;

	i = 0;
	while (i < map->nb_enemy)
	{
		map->sp_order[i] = i;
		map->sp_distance[i] = ((rc->player.pos.x - \
		map->enemies[i].pos.x) * (rc->player.pos.x - \
		map->enemies[i].pos.x) + (rc->player.pos.y - \
		map->enemies[i].pos.y) * (rc->player.pos.y - \
		map->enemies[i].pos.y));
		i++;
	}
	sort(map);
}

static void	init_var(t_data *data, t_raycast *rc, t_sprites *sp, int i)
{
	sp->sprite.x = data->map->enemies[data->map->sp_order[i]].pos.x \
	- rc->player.pos.x;
	sp->sprite.y = data->map->enemies[data->map->sp_order[i]].pos.y \
	- rc->player.pos.y;
	sp->transform.x = (rc->player.dir.y * sp->sprite.x \
		- rc->player.dir.x * sp->sprite.y);
	sp->transform.y = (-rc->player.plane.y * sp->sprite.x \
		+ rc->player.plane.x * sp->sprite.y);
	sp->sprite_screen = (int)((data->width / 2) \
		* (1 + sp->transform.x / sp->transform.y));
	sp->z_cor = rc->player.pitch + rc->player.posz / sp->transform.y;
	sp->size.y = abs((int)(data->height / sp->transform.y));
	sp->size.x = abs((int)(data->width / (sp->transform.y))) / 2;
}

static void	put_sprite(t_data *data, t_raycast *rc, t_sprites *sp)
{
	t_int_vector	i;
	int				d;

	i.x = sp->draw_start.x;
	while (i.x < sp->draw_end.x)
	{
		sp->tex.x = (i.x - (-sp->size.x / 2 + sp->sprite_screen)) \
		* data->map->en_sp->width / sp->size.x;
		i.y = sp->draw_start.y;
		if (sp->transform.y > 0 && i.x > 0 && i.x < data->width && \
			sp->transform.y < rc->z_buff_x[i.x])
		{
			while (i.y < sp->draw_end.y)
			{
				d = (i.y - sp->z_cor) * 256 + (sp->size.y - data->height) * 128;
				sp->tex.y = ((d * data->map->en_sp->height) / sp->size.y) / 256;
				sp->color = correct_color(&data->map->en_sp->pixels[
						(data->map->en_sp->width * sp->tex.y + sp->tex.x) * 4]);
				if (sp->color)
					data->buff[(i.y * data->width) + i.x] = sp->color;
				(i.y)++;
			}
		}
		(i.x)++;
	}
}

void	sprite(t_data *data, t_raycast *rc)
{
	t_sprites	sp;
	int			i;

	order_sprites(data->map, rc);
	i = -1;
	data->map->en_sp = data->map->en_sprites[0];
	while (++i < data->map->nb_enemy)
	{
		if (!data->map->enemies[data->map->sp_order[i]].status)
			continue ;
		init_var(data, rc, &sp, i);
		sp.draw_start.y = -sp.size.y / 2 + data->height / 2 + sp.z_cor;
		if (sp.draw_start.y < 0)
			sp.draw_start.y = 0;
		sp.draw_end.y = sp.size.y / 2 + data->height / 2 + sp.z_cor;
		if (sp.draw_end.y >= data->height)
			sp.draw_end.y = data->height - 1;
		sp.draw_start.x = -sp.size.x / 2 + sp.sprite_screen;
		if (sp.draw_start.x < 0)
			sp.draw_start.x = 0;
		sp.draw_end.x = sp.size.x / 2 + sp.sprite_screen;
		if (sp.draw_end.x >= data->width)
			sp.draw_end.x = data->width - 1;
		put_sprite(data, rc, &sp);
	}
}
