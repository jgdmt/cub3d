/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:22:41 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/04 18:52:30 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define WIDTH 1920
# define HEIGHT 1080

# define RSPEED 0.2
# define MSPEED 0.1

# define BLUE 0
# define ORANGE 1

# define ERR_MLX "Mlx crash."
# define ERR_MUTEX "Mutex crash."
# define ERR_ARGV "Wrong number of arguments."
# define ERR_MALLOC "Malloc error."
# define ERR_OUFLOW "Can't you count? RGB E [0, 255]"
# define ERR_RGB "RGB is 3 values, are you really a dev?"
# define ERR_NORGB "Void is not a color."
# define ERR_EMPTYPATH "Where is the path? >:("
# define ERR_NOMAP "The map is a lie."
# define ERR_UNKNOWNID "NO,SO,WE,EA,F or C only. It's not that hard, is it?"
# define ERR_PARSING "Parsing error. And you call yourself a student."
# define ERR_MAPNOTCLOSED "Do you need glasses? Close your map."
# define ERR_FORBIDDENCHAR "Forbidden character detected. Are you even trying?"
# define ERR_NOPLAYER "404 Player not found."
# define ERR_MANYPLAYERS "This is not a multiplayer game."
# define ERR_FILENAME "File name invalid."
# define ERR_FILEEXTENSION "File extension invalid."

# define MSG_END "You reached the end. Congratulations, your cake is waiting."

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

typedef struct s_portal
{
	int				status;
	t_int_vector	pos;
	t_int_vector	dir;
}	t_portal;

typedef struct s_player
{
	t_vector	pos;
	t_vector	plane;
	t_vector	dir;
	t_portal	portal[2];
	int			nb;
	int			pitch;
}	t_player;

typedef struct s_raycast
{
	int				draw_start;
	int				draw_end;
	int				line_height;
	t_int_vector	tex;
	t_int_vector	ipos;
	t_int_vector	step;
	int				side;
	int				x;
	int				y;
	t_vector		ray_dir;
	t_vector		delta_dist;
	t_vector		side_dist;
	t_player		player;
	double			perp_wall_dist;
	double			portal_first_ray;
	mlx_image_t		*t;
}	t_raycast;

typedef struct s_map
{
	char		**map;
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*we;
	mlx_image_t	*ea;
	mlx_image_t	*floor_color;
	mlx_image_t	*ceiling_color;
	size_t		max;
	int			fc[2];
}	t_map;

typedef struct s_data
{
	t_map			*map;
	t_player		*player;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*loading;
	size_t			time;
	char			**argv;
	uint32_t		*buff;
	int				inv;
	int				width;
	int				height;
	int				exit;
	pthread_mutex_t	lock;
}	t_data;

void	raycast(t_data *data);
void	*raycast_threader(void *data);
void	my_mlx_put_pixel(t_data *data, int x, int y, uint32_t color);
void	put_to_screen(t_data *data);
void	ft_usleep(size_t msec);
size_t	get_time(void);
void	loading_screen(t_data *data);
void	resize_render(t_data *data);
void	init_ray_param(int width, t_raycast *rc);
void	step_init(t_raycast *rc);
void	dda(t_data *data, t_raycast *rc);
void	portal(t_data *data, t_raycast *rc);
void	floor_cast(t_data *data);
int		correct_color(u_int8_t *pixel);

int		parsing(char *map_name, t_data *data);
void	get_infos(int fd, t_data *data);

void	free_all(char *str, int out, t_data *data);
void	free_smap(mlx_t *mlx, t_map *map);

void	close_window(void *gdata);
void	resize_window(int32_t width, int32_t height, void *gdata);
void	hook(void *data);
void	change_map(t_data *data);
void	menu(t_data *data);
void	portals(mouse_key_t button, action_t act, modifier_key_t mod, void *dt);
void	scroll(double xdelta, double ydelta, void *gdata);

#endif // CUB3D_BONUS_H
