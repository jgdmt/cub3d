/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:00:32 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/03 13:56:40 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	fill_player_infos(t_data *data, double dir[2], double plane[2]);
char	*fill_line(t_data *data, char *str);

static void	check_name(char *map_name)
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

static void	check_char(t_data *data, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		data->player->pos.x = x + 0.5f;
		data->player->pos.y = y + 0.5f;
		data->player->nb++;
		data->map->map[y][x] = '0';
		if (c == 'N')
			fill_player_infos(data, (double []){0, -1}, (double []){-1, 0});
		else if (c == 'S')
			fill_player_infos(data, (double []){0, 1}, (double []){1, 0});
		else if (c == 'E')
			fill_player_infos(data, (double []){-1, 0}, (double []){0, 1});
		else if (c == 'W')
			fill_player_infos(data, (double []){1, 0}, (double []){0, -1});
	}
	else if (c != '0' && c != '1' && c != ' ')
		free_all(ERR_FORBIDDENCHAR, 2, data);
}

static void	check_line(char *line, t_data *data, t_map *map, int i)
{
	size_t	j;

	j = 0;
	while (line[j])
	{
		check_char(data, line[j], i, j);
		if (line[j] == '0' || line[j] == 'N' || line[j] == 'S'
			|| line[j] == 'W' || line[j] == 'E')
		{
			if (j == 0 || j == data->map->max - 1
				|| i == 0 || i == ft_strslen(map->map) - 1)
				free_all(ERR_MAPNOTCLOSED, 2, data);
			if (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' '
				|| map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
				free_all(ERR_MAPNOTCLOSED, 2, data);
		}
		j++;
	}
}

static void	check_map(t_data *data, t_map *map)
{
	int		i;

	i = 0;
	while (map->map[i])
	{
		map->map[i] = fill_line(data, map->map[i]);
		map->map[i] = ft_strrev(map->map[i]);
		i++;
	}
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
		return (perror("cub3d"), free_all(0, 0, data), 1);
	get_infos(fd, data);
	close(fd);
	check_map(data, data->map);
	return (0);
}
