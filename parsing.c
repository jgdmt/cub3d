/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:00:32 by jgoudema          #+#    #+#             */
/*   Updated: 2024/03/14 12:34:55 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*fill_board(int *prev_next_length, t_map *map, int i);
int	strnlen(char *str, char c);

void	check_name(char *map_name)
{
	if (ft_strlen(map_name) < 4)
	{
		ft_printf(2, ERR_FILENAME);
		exit (0);
	}
	if (ft_strncmp(&map_name[ft_strlen(map_name) - 4], ".cub", 4))
	{
		ft_printf(2, ERR_FILEEXTENSION);
		exit (0);
	}
}

void	check_char(t_data *data, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		data->player->pos.x = x;
		data->player->pos.y = y;
		data->player->nb++;
		data->map->map[y][x] = '0';
	}
	if (c == 'N')
	{
		data->player->dir.x = 0;
		data->player->dir.y = -1;
		data->player->plane.x = -1;
		data->player->plane.y = 0;
	}
	else if (c == 'S')
	{
		data->player->dir.x = 0;
		data->player->dir.y = 1;
		data->player->plane.x = 1;
		data->player->plane.y = 0;
	}
	else if (c == 'W')
	{
		data->player->dir.x = -1;
		data->player->dir.y = 0;
		data->player->plane.x = 0;
		data->player->plane.y = 1;
		
	}
	else if (c == 'E')
	{
		data->player->dir.x = 1;
		data->player->dir.y = 0;
		data->player->plane.x = 0;
		data->player->plane.y = -1;
	}
	else if (c != '0' && c != '1' && c != ' ')
		free_all(ERR_FORBIDDENCHAR, 2, data);
}

void	check_line(char *line, t_data *data, t_map *map, int i)
{
	int	l[2];
	int	j;

	fill_board(l, map, i);
	j = 0;
	while (line[j] && line[j] != '\n')
	{
		check_char(data, line[j], i, j);
		if (line[j] == '0' || line[j] == 'N' || line[j] == 'S'
			|| line[j] == 'W' || line[j] == 'E')
		{
			if (j == 0 || j == strnlen(line, '\n') - 1 || l[0] <= j
				|| l[1] <= j || i == 0 || i == ft_strslen(map->map) - 1)
				free_all(ERR_MAPNOTCLOSED, 2, data);
			if (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' '
				|| map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
				free_all(ERR_MAPNOTCLOSED, 2, data);
		}
		j++;
	}
}

void	check_map(t_data *data, t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		check_line(map->map[i], data, map, i);
		i++;
	}
	if (data->player->nb == 0)
		free_all(ERR_NOPLAYER, 2, data);
	if (data->player->nb > 1)
		free_all(ERR_MANYPLAYERS, 2, data);
}

int	parsing(char *map_name, t_data *data)
{
	int	fd;

	check_name(map_name);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (perror("cub3d"), 1);
	get_infos(fd, data);
	close(fd);
	check_map(data, data->map);
	return (0);
}