/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:23:56 by jgoudema          #+#    #+#             */
/*   Updated: 2024/03/12 12:40:33 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	get_map(int fd, t_map *map)
{
	char	*line;
	char	**temp;

	map->map = ft_calloc(2, sizeof(char *));
	if (!map->map)
		return (ft_printf(2, "Error\nMalloc error.\n"), 1);
	map->map[0] = get_next_line(fd);
	while (map->map[0] && map->map[0][0] == '\n')
	{
		free(map->map[0]);
		map->map[0] = get_next_line(fd);
	}
	if (!map->map[0])
		return (ft_printf(2, "Error\nThe map is a lie.\n"), 1);
	line = "";
	while (line && line[0] != '\n')
	{
		line = get_next_line(fd);
		temp = map->map;
		map->map = ft_arrayjoin(map->map, &line, 1);
		free(temp);
		if (!map->map)
			return (ft_printf(1, "Error\nMalloc error.\n"), 1);
	}
	return (0);

	int i = 0;
	while (map->map[i])
		ft_printf(1, "%s", map->map[i++]);
}

static int	get_elements(char *line, t_map *map, int infos)
{
	if (line[0] == '\n')
		return (infos);
	else if (!ft_strncmp(line, "NO ", 3))
		map->no_texture = strdup_to(line, 3);
	else if (!ft_strncmp(line, "SO ", 3))
		map->so_texture = strdup_to(line, 3);
	else if (!ft_strncmp(line, "WE ", 3))
		map->we_texture = strdup_to(line, 3);
	else if (!ft_strncmp(line, "EA ", 3))
		map->ea_texture = strdup_to(line, 3);
	else if (!ft_strncmp(line, "F ", 2))
		map->floor_color = 1;
	else if (!ft_strncmp(line, "C ", 2))
		map->ceiling_color = 1;
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
		free_all("Error\nUnknown identifier.\n", 2, data->map_data);
	if (infos == -2)
		free_all("Error\nParsing error.\n", 2, data->map_data);
	if (infos < 6)
		free_all("Error\nMissing identifier(s).\n", 2, data->map_data);
	if (get_map(fd, data->map_data))
	{
		close(fd);
		free_all(0, 0, data->map_data);
	}
}
