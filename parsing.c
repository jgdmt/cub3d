/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:00:32 by jgoudema          #+#    #+#             */
/*   Updated: 2024/03/11 19:24:54 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_name(char *map_name)
{
	if (ft_strlen(map_name) < 4)
	{
		ft_printf(2, "Error\nFile name invalid.\n");
		exit (0);
	}
	if (ft_strncmp(&map_name[ft_strlen(map_name) - 4], ".cub", 4))
	{
		ft_printf(2 ,"Error\nFile extension invalid.\n");
		exit (0);
	}
}

int	strnlen(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

void	check_char(t_data *data, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		data->player->x = x;
		data->player->y = y;
	}
	if (c == 'N')
		data->player->direction = 0;
	else if (c == 'S')
		data->player->direction = 1;
	else if (c == 'W')
		data->player->direction = 2;
	else if (c == 'E')
		data->player->direction = 3;
	else if (c != '0' && c != '1' && c != ' ')
		free_all("Error\nForbidden character detected.\n", 2, data->map_data);
}

void	check_line(char *line, t_data *data, t_map *map, int i)
{
	int	pl;
	int	nl;
	int	j;

	pl = 0;
	nl = 0;
	if (i > 0)
		pl = strnlen(map->map[i - 1], '\n');
	if (map->map[i + 1])
		nl = strnlen(map->map[i + 1], '\n');
	j = 0;
	while (line[j] && line[j] != '\n')
	{
		check_char(data, line[j], i, j);
		if (line[j] == '0')
		{
			if (j == 0 || j == strnlen(line, '\n') - 1 || pl <= j || nl <= j
				|| i == 0 || i == ft_strslen(map->map) - 1)
				free_all("Error\nMap not closed.\n", 2, map);
			if (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' '
				|| map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
				free_all("Error\nMap not closed.\n", 2, map);
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
	if (data->player->x < 0 || data->player->y < 0)
		free_all("Error\n404 Player not found.\n", 2, map);
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
	check_map(data, data->map_data);
	return (0);
}
