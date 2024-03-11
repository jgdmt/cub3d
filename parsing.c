/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:00:32 by jgoudema          #+#    #+#             */
/*   Updated: 2024/03/11 15:29:37 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	get_map(int fd, t_data *data)
// {
// 	char	*temp;

// }

int	check_name(char *map_name)
{
	if (ft_strlen(map_name) < 4)
		return (ft_printf(2, "Error: file name invalid.\n"), 1);
	if (ft_strncmp(&map_name[ft_strlen(map_name) - 4], ".cub", 4))
		return (ft_printf(2 ,"Error: file extension invalid.\n"), 1);
	return (0);
}

char	*strdup_to(char *line, int start)
{
	char	*path;
	int		j;

	j = 0;
	path = malloc(ft_strlen(line) - start + 1);
	if (!path)
		return (NULL);
	while (line[start] && line[start] != '\n')
		path[j++] = line[start++];
	path[j] = 0;
	ft_printf(1, "path %s\n", path);
	return (path);
}

int	get_elements(char *line, t_data *data, int infos)
{
	if (line[0] == '\n')
		return (infos);
	else if (!ft_strncmp(line, "NO ", 3))
		data->map_data->no_texture = strdup_to(line, 3);
	else if (!ft_strncmp(line, "SO ", 3))
		data->map_data->so_texture = strdup_to(line, 3);
	else if (!ft_strncmp(line, "WE ", 3))
		data->map_data->we_texture = strdup_to(line, 3);
	else if (!ft_strncmp(line, "EA ", 3))
		data->map_data->ea_texture = strdup_to(line, 3);
	else if (!ft_strncmp(line, "F ", 2))
		data->map_data->no_texture = strdup_to(line, 2);
	else if (!ft_strncmp(line, "C ", 3))
		data->map_data->no_texture = strdup_to(line, 2);
	else
		return (-1);
	return (infos + 1);
}

void	get_infos(int fd, t_data *data)
{
	char	*line;
	int		infos;

	(void) data;
	infos = 0;
	line = get_next_line(fd);
	while (line && (infos != 6 || line != -1))
	{
		infos = get_elements(line, data, infos);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (infos == -1)
		free_all("Error: Unknown identifier.\n", 2, data);
	if (infos < 6)
		free_all("Error: missing identifier(s).\n", 2, data);
}

int	parsing(char *map_name, t_data *data)
{
	int	fd;

	if (check_name(map_name))
		exit (0);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (perror("cub3d"), 1);
	get_infos(fd, data);

	return (0);
}
