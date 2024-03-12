/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:23:56 by jgoudema          #+#    #+#             */
/*   Updated: 2024/03/12 15:54:56 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*strdup_to(char *line, int start);

char	*check_texture(char *line, int start, t_map *map)
{
	char	*text;

	if (ft_strlen(line) - start == 1)
		return (free(line), free_all(ERR_EMPTYPATH, 2, map), 2);
	text = strdup_to(line, start);
	return (text);
}

int	check_color(char *line, int start, t_map *map)
{
	int	rgb[3];
	int	i;
	int	j;

	if (ft_strlen(line) - start == 1)
		return (free(line), free_all(ERR_EMPTYRGB, 2, map), 1);
	i = start;
	j = 0;
	while (line[i] && j < 3)
	{
		rgb[j++] = ft_atoi(line + i);
		if (rgb[j - 1] > 255 || rgb[j - 1] < 0)
			return (free(line), free_all(ERR_OUFLOW, 2, map), 1);
		while (line[i] && line[i] != '\n' && line[i] != ',')
			if (line[i++] != ' ' && line[i - 1] != ','
				&& !ft_isdigit(line[i - 1]))
				return (free(line), free_all(ERR_OUFLOW, 2, map), 1);
		if (line[i] == ',')
			i++;
	}
	if (j != 3 || (line[i] && line[i] != '\n') || line[i - 1] == ',')
		return (free(line), free_all(ERR_RGB, 2, map), 1);
	return (255 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

static int	get_map(int fd, t_map *map)
{
	char	*line;
	char	**temp;

	map->map = ft_calloc(2, sizeof(char *));
	if (!map->map)
		return (ft_printf(2, ERR_MALLOC), 1);
	map->map[0] = get_next_line(fd);
	while (map->map[0] && map->map[0][0] == '\n')
	{
		free(map->map[0]);
		map->map[0] = get_next_line(fd);
	}
	if (!map->map[0])
		return (ft_printf(2, ERR_NOMAP), 1);
	line = "";
	while (line && line[0] != '\n')
	{
		line = get_next_line(fd);
		temp = map->map;
		map->map = ft_arrayjoin(map->map, &line, 1);
		free(temp);
		if (!map->map)
			return (ft_printf(1, ERR_MALLOC), 1);
	}
	return (0);
}

static int	get_elements(char *line, t_map *map, int infos)
{
	if (line[0] == '\n')
		return (infos);
	else if (!ft_strncmp(line, "NO ", 3))
		map->no_texture = check_texture(line, 3, map);
	else if (!ft_strncmp(line, "SO ", 3))
		map->so_texture = check_texture(line, 3, map);
	else if (!ft_strncmp(line, "WE ", 3))
		map->we_texture = check_texture(line, 3, map);
	else if (!ft_strncmp(line, "EA ", 3))
		map->ea_texture = check_texture(line, 3, map);
	else if (!ft_strncmp(line, "F ", 2))
		map->floor_color = check_color(line, 2, map);
	else if (!ft_strncmp(line, "C ", 2))
		map->ceiling_color = check_color(line, 2, map);
	else
		return (-1);
	if (infos + 1 == 6 && (!map->no_texture || !map->so_texture
			|| !map->we_texture || !map->ea_texture || map->floor_color == -1
			|| map->ceiling_color == -1))
		return (-2);
	return (infos + 1);
}

void	get_infos(int fd, t_data *data)
{
	char	*line;
	int		infos;

	infos = 0;
	line = get_next_line(fd);
	while (line && infos != 6 && infos >= 0)
	{
		infos = get_elements(line, data->map_data, infos);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (infos == -1 || infos == -2 || infos < 6)
		close (fd);
	if (infos == -1)
		free_all(ERR_UNKNOWNID, 2, data->map_data);
	if (infos == -2)
		free_all(ERR_PARSING, 2, data->map_data);
	if (infos < 6)
		free_all(ERR_MISSINGID, 2, data->map_data);
	if (get_map(fd, data->map_data))
	{
		close(fd);
		free_all(0, 0, data->map_data);
	}
}
