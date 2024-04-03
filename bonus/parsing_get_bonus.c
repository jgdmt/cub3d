/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:23:56 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/03 16:53:38 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*strdup_to(char *line, int start);
void	add_color(char t, t_data *data);
char	**ft_modif_split(char *str, char *sep);
void	split_free(char **array, int len);

static mlx_image_t	*check_texture(char *line, int start, t_data *data)
{
	char			*text;
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	if (ft_strlen(line) - start == 1)
		return (free(line), free_all(ERR_EMPTYPATH, 2, data), NULL);
	text = strdup_to(line, start);
	texture = mlx_load_png(text);
	free(text);
	if (!texture)
		return (free(line), free_all(ERR_MLX, 2, data), NULL);
	img = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	if (!img)
		return (free(line), free_all(ERR_MLX, 2, data), NULL);
	return (img);
}

static u_int32_t	check_color(char *l, char t, t_data *data)
{
	int		rgb[3];
	char	**col;
	int		i;

	add_color(t, data);
	col = ft_modif_split(l, " ,\n");
	if (!col)
		return (free(l), free_all(ERR_MALLOC, 2, data), 1);
	if (ft_strslen(col) == 1)
		return (split_free(col, -1), free(l), free_all(ERR_NORGB, 2, data), 1);
	if (ft_strslen(col) != 4)
		return (split_free(col, -1), free(l), free_all(ERR_RGB, 2, data), 1);
	i = -1;
	while (++i < 3)
	{
		rgb[i] = ft_atoi(col[i + 1]);
		if (ft_strlen(col[i + 1]) > 3 || rgb[i] > 255 || rgb[i] < 0)
			return (split_free(col, -1), free(l),
				free_all(ERR_OUFLOW, 2, data), 1);
	}
	split_free(col, -1);
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255);
}

static int	get_map(int fd, char *line, t_map *map)
{
	char	**temp;

	map->map = ft_calloc(2, sizeof(char *));
	if (!map->map)
		return (free(line), ft_printf(2, "%s", ERR_MALLOC), 1);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	map->map[0] = line;
	if (!map->map[0])
		return (ft_printf(2, "%s", ERR_NOMAP), 1);
	while (line && line[0] != '\n')
	{
		if (ft_strlen(line) > map->max)
			map->max = ft_strlen(line);
		line = get_next_line(fd);
		temp = ft_arrayjoin(map->map, &line, 1);
		if (!temp)
			return (free(line), ft_printf(1, ERR_MALLOC), 1);
		free(map->map);
		map->map = temp;
	}
	return (0);
}

static int	get_elements(char *line, t_data *data, t_map *map, int infos)
{
	if (line[0] == '\n')
		return (infos);
	else if (!ft_strncmp(line, "NO ", 3))
		map->no = check_texture(line, 3, data);
	else if (!ft_strncmp(line, "SO ", 3))
		map->so = check_texture(line, 3, data);
	else if (!ft_strncmp(line, "WE ", 3))
		map->we = check_texture(line, 3, data);
	else if (!ft_strncmp(line, "EA ", 3))
		map->ea = check_texture(line, 3, data);
	else if (!ft_strncmp(line, "F ", 2))
		map->floor_color = check_color(line, 'F', data);
	else if (!ft_strncmp(line, "C ", 2))
		map->ceiling_color = check_color(line, 'C', data);
	else
		return (-1);
	if (infos + 1 == 6 && (!map->no || !map->so
			|| !map->we || !map->ea || map->fc[0] != 1
			|| map->fc[1] != 1))
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
		infos = get_elements(line, data, data->map, infos);
		free(line);
		line = get_next_line(fd);
	}
	if (infos == -1 || infos == -2)
		close (fd);
	if (infos == -1 || infos == -2)
		free(line);
	if (infos == -1)
		free_all(ERR_UNKNOWNID, 2, data);
	if (infos == -2)
		free_all(ERR_PARSING, 2, data);
	if (get_map(fd, line, data->map))
	{
		close(fd);
		free_all(0, 0, data);
	}
}
