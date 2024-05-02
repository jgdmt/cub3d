/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:18:12 by jgoudema          #+#    #+#             */
/*   Updated: 2024/05/02 15:35:26 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	add_line(t_map *map)
{
	int		i;
	char	*line;
	char	**tmp;

	i = 0;
	while (map->map[i])
		i++;
	if (map->map[i - 1][0] != '\n')
	{
		line = ft_strdup("\n");
		if (!line)
			return (ft_printf(2, ERR_MALLOC), 1);
		tmp = ft_arrayjoin(map->map, &line, 1);
		if (!tmp)
			return (free(line), ft_printf(2, ERR_MALLOC), 1);
		free(map->map);
		map->map = tmp;
	}
	return (0);
}

/**
 * @brief Fills the data::player informations.
 * 
 * @param data structure with all program data
 * @param dir vector of direction of the player
 * @param plane plane of the player
 */
void	fill_player_infos(t_data *data, double dir[2], double plane[2])
{
	data->player->dir.x = dir[0];
	data->player->dir.y = dir[1];
	data->player->plane.x = plane[0];
	data->player->plane.y = plane[1];
}

/**
 * @brief Copies a string from a certain start.
 * 
 * @param line line to be copied
 * @param start start of the duplication
 * @return char* 
 */
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

/**
 * @brief Fills a line with spaces.
 * 
 * @param data structure with all program data
 * @param str the line to be filled
 * @return char* 
 */
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

/**
 * @brief Frees an array and may exit.
 * 
 * @param data structure with all program data
 * @param msg message to exit with
 * @param strs array to be free
 * @param ex 1 to exit, 0 otherwise
 */
void	free_ex(t_data *data, char *msg, char **strs, int ex)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	if (ex)
		free_all(msg, 2, data);
}
