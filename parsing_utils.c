/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:18:12 by jgoudema          #+#    #+#             */
/*   Updated: 2024/03/14 17:38:57 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_player_infos(t_data *data, double dir[2], double plane[2])
{
	data->player->dir.x = dir[0];
	data->player->dir.y = dir[1];
	data->player->plane.x = plane[0];
	data->player->plane.y = plane[1];
}

void	add_color(char t, t_data *data)
{
	if (t == 'C')
		data->map->fc[1]++;
	else if (t == 'F')
		data->map->fc[0]++;
}

char	*strdup_to(char *line, int start)
{
	char	*path;
	int		j;

	j = 0;
	while (line[start] && line[start] == ' ')
		start++;
	path = malloc(ft_strlen(line) - start + 1);
	if (!path)
		return (NULL);
	while (line[start] && line[start] != '\n')
		path[j++] = line[start++];
	path[j] = 0;
	return (path);
}

int	strnlen(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

int	*fill_board(int *prev_next_length, t_map *map, int i)
{
	prev_next_length[0] = 0;
	prev_next_length[1] = 0;
	if (i > 0)
		prev_next_length[0] = strnlen(map->map[i - 1], '\n');
	if (map->map[i + 1])
		prev_next_length[1] = strnlen(map->map[i + 1], '\n');
	return (prev_next_length);
}
