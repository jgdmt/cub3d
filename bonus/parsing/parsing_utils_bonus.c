/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:18:12 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/09 19:31:47 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	fill_player_infos(t_data *data, double dir[2], double plane[2])
{
	data->player->dir.x = dir[0];
	data->player->dir.y = dir[1];
	data->player->plane.x = plane[0];
	data->player->plane.y = plane[1];
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
	while (line[start] && line[start] != '\n' && line[start] != ' ')
		path[j++] = line[start++];
	path[j] = 0;
	return (path);
}

char	*fill_line(t_data *data, char *str)
{
	size_t	i;
	char	*s;

	s = malloc(data->map->max + 1);
	if (!s)
		free_all(ERR_MALLOC, 2, data);
	i = 0;
	while (str[i])
	{
		s[i] = str[i];
		if (s[i] == '3')
			data->map->nb_enemy++;
		if (s[i] == '\n')
			s[i] = ' ';
		i++;
	}
	while (i < data->map->max)
		s[i++] = ' ';
	s[i] = 0;
	free(str);
	return (s);
}
