/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:22:41 by vilibert          #+#    #+#             */
/*   Updated: 2024/03/14 15:39:00 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

# define WIDTH 1920
# define HEIGHT 1080

# define RSPEED 0.2
# define MSPEED 0.1

# define ERR_MLX "Error\nMlx crash.\n"
# define ERR_ARGV "Error\nWrong number of arguments.\n"
# define ERR_MALLOC "Error\nMalloc error.\n"
# define ERR_OUFLOW "Error\nCan't you count? RGB E [0, 255]\n"
# define ERR_RGB "Error\nRGB is 3 values :(.\n"
# define ERR_EMPTYRGB "Error\nVoid is not a color.\n"
# define ERR_EMPTYPATH "Error\nWhere is the path? >:(\n"
# define ERR_NOMAP "Error\nThe map is a lie.\n"
# define ERR_UNKNOWNID "Error\nUnknown identifier.\n"
# define ERR_PARSING "Error\nParsing error.\n"
// # define ERR_MISSINGID "Error\nMissing identifier(s).\n"
# define ERR_MAPNOTCLOSED "Error\nMap not closed.\n"
# define ERR_FORBIDDENCHAR "Error\nForbidden character detected.\n"
# define ERR_NOPLAYER "Error\n404 Player not found.\n"
# define ERR_MANYPLAYERS "Error\nThis is not a multiplayer game.\n"
# define ERR_FILENAME "Error\nFile name invalid.\n"
# define ERR_FILEEXTENSION "Error\nFile extension invalid.\n"

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_int_vector
{
	int	x;
	int	y;
}	t_int_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	plane;
	t_vector	dir;
	int			nb;
}	t_player;

typedef struct s_raycast
{
	int	draw_start;
	int	draw_end;
	int	line_height;
	t_int_vector tex;
	t_int_vector ipos;
	t_int_vector step;
	int	side;
	int	x;
	int	y;
	t_vector ray_dir;
	t_vector delta_dist;
	t_vector	side_dist;
	double perpWallDist;
}	t_raycast;

typedef struct s_map
{
	char		**map;
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*we;
	mlx_image_t	*ea;
	int			floor_color;
	int			ceiling_color;
	int			fc[2];
}	t_map;

typedef struct s_data
{
	t_map		*map;
	t_player	*player;
	mlx_t		*mlx;
	mlx_image_t	*img;
	size_t		time;
	int			width;
	int			height;
}	t_data;

void	raycast(t_data *data);

int		parsing(char *map_name, t_data *data);
void	get_infos(int fd, t_data *data);

void	free_all(char *str, int out, t_data *data);

void	keypress(mlx_key_data_t key, void *data);
void	close_window(void *gdata);
void	resize_window(int32_t width, int32_t height, void *gdata);

#endif // CUB3D_H
