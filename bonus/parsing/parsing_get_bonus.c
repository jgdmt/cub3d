/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:23:56 by jgoudema          #+#    #+#             */
/*   Updated: 2024/04/23 16:49:29 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

char	*strdup_to(char *line, int start);
void	add_color(char t, t_data *data);
char	**ft_modif_split(char *str, char *sep);
void	split_free(char **array, int len);
void	free_ex(t_data *data, char **strs, int ex);

/**
 * @brief Checks if the given texture exists and turns
 * it into an image.
 * 
 * @param line line with the path of the texture
 * @param start start of the path in the line
 * @param data structure with all program data
 * @return mlx_image_t* 
 */
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
		return (NULL);
	img = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	if (!img)
		return (NULL);
	return (img);
}

// static u_int32_t	check_color(char *l, char t, t_data *data)
// {
// 	int		rgb[3];
// 	char	**col;
// 	int		i;

// 	add_color(t, data);
// 	col = ft_modif_split(l, " ,\n");
// 	if (!col)
// 		return (free(l), free_all(ERR_MALLOC, 2, data), 1);
// 	if (ft_strslen(col) == 1)
// 		return (split_free(col, -1), free(l), free_all(ERR_NORGB, 2, data), 1);
// 	if (ft_strslen(col) != 4)
// 		return (split_free(col, -1), free(l), free_all(ERR_RGB, 2, data), 1);
// 	i = -1;
// 	while (++i < 3)
// 	{
// 		rgb[i] = ft_atoi(col[i + 1]);
// 		if (ft_strlen(col[i + 1]) > 3 || rgb[i] > 255 || rgb[i] < 0)
// 			return (split_free(col, -1), free(l),
// 				free_all(ERR_OUFLOW, 2, data), 1);
// 	}
// 	split_free(col, -1);
// 	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255);
// }

/**
 * @brief Gets the (char **) data::map::map object.
 * 
 * @param fd file descriptor of the map file
 * @param line starting line of the parsing of the (char **) map
 * @param map structure with all data about the map
 * @return int 
 */
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

/**
 * @brief Get the sprites of the enemies.
 * 
 * @param line contains the paths of the different sprites
 * @param start start of the paths
 * @param data structure with all program data
 * @param map structure with all data about the map
 */
void	get_sprite(char *line, int start, t_data *data, t_map *map)
{
	char	**text;
	int		i;

	while (start-- > 0 || *line == ' ')
		line++;
	if (!ft_strncmp(line, "NONE", 4))
		return ;
	text = ft_modif_split(line, ",");
	if (!text)
		free_all(ERR_MALLOC, 2, data);
	map->en_sprites = ft_calloc(ft_strslen(text) + 1, sizeof(mlx_image_t));
	if (!map->en_sprites)
		free_ex(data, text, 1);
	i = 0;
	while (text[i])
	{
		map->en_sprites[i] = check_texture(text[i], 0, data);
		if (!map->en_sprites[i])
			free_ex(data, text, 1);
		i++;
	}
	free_ex(data, text, 0);
}

/**
 * @brief Gets informations related to the textures of the game.
 * 
 * @param line line to be checked
 * @param data structure with all program data
 * @param map structure with all data about the map
 * @param infos number of informations already got
 * @return int
 */
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
		map->floor_color = check_texture(line, 2, data);
	else if (!ft_strncmp(line, "C ", 2))
		map->ceiling_color = check_texture(line, 2, data);
	else if (!ft_strncmp(line, "E ", 2))
		get_sprite(line, 2, data, map);
	else
		return (-1);
	if (infos + 1 == 7 && (!map->no || !map->so
			|| !map->we || !map->ea || !map->ceiling_color
			|| !map->floor_color))
		return (-2);
	return (infos + 1);
}

/**
 * @brief Gets the informations for the structure data::map
 * by calling other functions.
 * 
 * @param fd file descriptor of the map file
 * @param data structure with all program data
 */
void	get_infos(int fd, t_data *data)
{
	char	*line;
	int		infos;

	infos = 0;
	line = get_next_line(fd);
	while (line && infos != 7 && infos >= 0)
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
