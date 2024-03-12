/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:22:41 by vilibert          #+#    #+#             */
/*   Updated: 2024/03/12 15:17:29 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

# define ERR_MALLOC "Error\nMalloc error.\n"
# define ERR_OUFLOW "Error\nCan't you count? 0 <= RGB <= 255\n"
# define ERR_RGB "Error\nRGB is 3 values :(.\n"
# define ERR_EMPTYRGB "Error\nVoid is not a color.\n"
# define ERR_EMPTYPATH "Error\nWhere is the path? >:(\n"
# define ERR_NOMAP "Error\nThe map is a lie.\n"
# define ERR_UNKNOWNID "Error\nUnknown identifier.\n"
# define ERR_PARSING "Error\nParsing error.\n"
# define ERR_MISSINGID "Error\nMissing identifier(s).\n"
# define ERR_MAPNOTCLOSED "Error\nMap not closed.\n"
# define ERR_FORBIDDENCHAR "Error\nForbidden character detected.\n"
# define ERR_NOPLAYER "Error\n404 Player not found.\n"
# define ERR_MANYPLAYERS "Error\nThis is not a multiplayer game.\n"
# define ERR_FILENAME "Error\nFile name invalid.\n"
# define ERR_FILEEXTENSION "Error\nFile extension invalid.\n"

typedef	struct s_player
{
	double	x;
	double	y;
	int		nb;
	int		direction; // temp
}	t_player;

typedef struct s_map
{
	char	**map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color;
	int		ceiling_color;
}	t_map;

typedef struct s_data
{
	t_map		*map_data;
	t_player	*player;
}	t_data;

void raycast_test(void);

int		parsing(char *map_name, t_data *data);
void	get_infos(int fd, t_data *data);

void	free_all(char *str, int out, t_map *map);

#endif // CUB3D_H
