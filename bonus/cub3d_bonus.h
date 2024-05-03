/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:22:41 by vilibert          #+#    #+#             */
/*   Updated: 2024/05/03 12:36:01 by jgoudema         ###   ########.fr       */
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
# include <stdatomic.h>

# define WIDTH 1920
# define HEIGHT 1080

# define RSPEED 0.1
# define ACCELERATION 0.01
# define MAXV	0.03
# define INERTIA 0.0005

# define BLUE 0
# define ORANGE 1

# define ERR_MLX "Mlx crash."
# define ERR_MUTEX "Mutex crash."
# define ERR_ARGV "Wrong number of arguments."
# define ERR_MALLOC "Malloc error. Congratulations for your failure!"
# define ERR_OUFLOW "Can't you count? RGB E [0, 255]"
# define ERR_RGB "RGB is 3 values, are you really a dev?"
# define ERR_NORGB "Void is not a color."
# define ERR_EMPTYPATH "Where is the path? >:("
# define ERR_NOMAP "The map is a lie."
# define ERR_UNKNOWNID "NO,SO,WE,EA,F,E or C only. It's not that hard, is it?"
# define ERR_PARSING "Parsing error. And you call yourself a student."
# define ERR_MAPNOTCLOSED "Do you need glasses? Close your map."
# define ERR_FORBIDDENCHAR "Forbidden character detected. Are you even trying?"
# define ERR_NOPLAYER "404 Player not found."
# define ERR_MANYPLAYERS "This is not a multiplayer game."
# define ERR_DOORS "You can't be so bad that you need more than one exit door."
# define ERR_ENCLOSE "For your own security, do not put enemy too close to you."
# define ERR_ENEMIES "Too many enemies. Do not bite more than you can chew."
# define ERR_ENTEX "No enemies sprites. Your carelessness is disappointing."
# define ERR_NBENTEX "I thought 4 enemy sprites was obvious. Ah humans."
# define ERR_FILENAME "File name invalid."
# define ERR_FILEEXTENSION "File extension invalid."

# define MSG_END "You reached the end. Congratulations, your cake is waiting."
# define MSG_DEATH "Tests results: humans are too weak. NB: upgrade to robots."
# define MSG_GAMEQUIT "You've already ragequit? Not surprising coming from you."
# define MSG_NEXT1_1 "I should praise you for the finally flawless parsing.\n"
# define MSG_NEXT1_2 "'Congratulations for achieving such a simple task!'\n"
# define MSG_NEXT1_3 "I heard humans were happy with meaningless words.\n"
# define MSG_NEXT2_1 "What, were you expecting more? Get over yourself."
# define MSG_NEXT2_2 " It's just parsing.\n"

/**
 * @brief Simple 2D vector structure that uses doubles.
 * 
 */
typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

/**
 * @brief Dimple 2D vector structure that uses integers.
 * 
 */
typedef struct s_int_vector
{
	int	x;
	int	y;
}	t_int_vector;

/**
 * @brief Minimum set of informations per portal.
 * @param pos coordonates in t_data::map::map
 * @param dir directional vector (can only represent the four cardinal direction)
 * @param status simple on/off bool
 */
typedef struct s_portal
{
	bool			status;
	t_int_vector	pos;
	t_int_vector	dir;
}	t_portal;

/**
 * @brief Minimum set of informations per enemy.
 * @param pos coordonates in t_data::map::map
 * @param status simple on/off bool
 * @param life a HP score that start at 3
 */
typedef struct s_enemy
{
	t_vector	pos;
	bool		status;
	int			life;
}	t_enemy;

/**
 * @brief Represent all the data for a raycast camera.
 * @param pos exact coordonates in t_data::map::map
 * @param dir direction of the camera
 * @param plane represent a plane that is used to calculate ray length, anti phis
 * @param mdir
 * @param portal structure with informations about the portals
 * @param nb
 * @param posz
 * @param pitch
 * @param vx
 * @param vy
 */
typedef struct s_player
{
	t_vector				pos;
	t_vector				plane;
	t_vector				dir;
	t_vector				mdir;
	t_portal				portal[2];
	int						nb;
	int						posz;
	int						pitch;
	int						hp;
	_Atomic double			vx;
	_Atomic double			vy;
	_Atomic double			vz;
}	t_player;

typedef struct s_hud
{
	int			width;
	int			height;
	int			hidden;
	mlx_image_t	*menu[12];
	mlx_image_t *img;
	uint32_t	*buff;
}	t_hud;

/**
 * @brief 
 * @param draw_start minimum y to print a wall column on the screen
 * @param draw_end maximum y to print a wall column on the screen
 * @param line_height length of a wall column on the screen
 * @param tex uses for calculate coordonate of a pixel inside texture buff
 * @param ipos represent rasterized coordonate hit by a ray
 * @param step directional increment for ipos
 * @param side represents if the wall hit in ipos is "horizontal or vertical"
 * @param x coordonate in the screen
 * @param y coordonate in the screen
 * @param ray_dir direction of each ray
 * @param delta_dist 
 * @param side_dist
 * @param player a copy of t_data::player for avoiding data races
 * @param perp_wall_dist length of the ray relative to the plan + 
 * eventual portal ray length
 * @param portal_first_ray length of each portal ray
 * @param t pointer to the correct(cardinal oriented texture) texture of wall
 * 
 */
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
	double			z_buff_x[3840];
	mlx_image_t		*t;
	bool			print;
}	t_raycast;

typedef struct s_sprites
{
	t_vector		sprite;
	t_vector		transform;
	t_int_vector	draw_start;
	t_int_vector	draw_end;
	t_int_vector	size;
	t_int_vector	tex;
	int				z_cor;
	int				sprite_screen;
	uint32_t		color;
}	t_sprites;

/**
 * @brief 
 * @param map array containing the map itself
 * @param no texture the north
 * @param so texture the south
 * @param we texture of the west
 * @param ea texture of the east
 * @param floor_color texture of the floor
 * @param ceiling_color texture of the ceiling
 * @param en_sprites texture of the enemies
 * @param enemies array of enemies
 * @param door_stat status of the door
 * @param door_pos position of the door
 * @param nb_enemy number of enemies
 * @param max length maximal of the map in x
 * @param maxy length maximal of the map in y
 */
typedef struct s_map
{
	char		**map;
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*we;
	mlx_image_t	*ea;
	mlx_image_t	*floor_color;
	mlx_image_t	*ceiling_color;
	mlx_image_t	**en_sprites;
	mlx_image_t	*door_open;
	mlx_image_t	*door_close;
	mlx_image_t	*en_sp;
	t_enemy		*enemies;
	int			*sp_order;
	double		*sp_distance;
	int			door_stat;
	t_vector	door_pos;
	int			nb_enemy;
	size_t		max;
	size_t		maxy;
}	t_map;

/**
 * @brief 
 * @param map structure with informations about the map
 * @param player structure with informations about the player
 * @param mlx mlx pointer
 * @param img
 * @param loading texture of the loading screen
 * @param cursor textures of the cursors
 * @param buff copy buffer of the t_data::img 
 * @param time 
 * @param argv
 * @param inv inventory slot in current usage
 * @param width width of the window
 * @param height height of the window
 * @param exit exit flag to freeze the game
 */
typedef struct s_data
{
	t_map			*map;
	t_player		*player;
	t_hud			hud;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*loading;
	mlx_image_t		*cursor[5];
	mlx_image_t		*portal[4];
	mlx_image_t		*portal_gun[10];
	mlx_image_t		*gun[5];
	uint32_t		*buff;
	size_t			time;
	char			**argv;
	int				inv;
	_Atomic int		portal_shot;
	_Atomic int		gun_shot;
	int				width;
	int				height;
	_Atomic int		exit;
}	t_data;

void		*raycast_threader(void *data);
void		my_mlx_put_pixel(t_data *data, int x, int y, uint32_t color);
void		put_to_screen(t_data *data);
void		ft_usleep(size_t msec);
size_t		get_time(void);
void		resize_render(t_data *data);
void		cast_a_ray(t_data *data, t_raycast *rc, int deep);
void		portal(t_data *data, t_raycast *rc, int from, int deep);
void		floor_cast(t_data *data, t_player player);
int			correct_color(u_int8_t *pixel);
void		get_tex_ptr(t_data *data, t_raycast *rc);
void		init(t_raycast *rc);
void		rot_vector(t_vector *v1, t_int_vector *p1, t_int_vector *p2);
void		*update_inertia(void *gdata);
void		print_ray(t_data *data, t_raycast *rc);
void		sprite(t_data *data, t_raycast *rc);

void		init_ray_param(int width, t_raycast *rc);
void		step_init(t_raycast *rc);

void		loading_screen(t_data *data);
void		cursor_screen(t_data *data);
void		guns_screen(t_data *data);

void		*thread_hud(void *gdata);
void		init_thread(t_data *data);
void		print_hp(t_data *data);
void		get_minimap(t_data *data);

t_data		init_data(t_map *map, t_player *player, mlx_t *mlx, char **argv);
t_map		init_map(void);
t_player	init_player(void);

mlx_image_t	*create_image(mlx_t *mlx, char*(text)(int), int i);
void		init_portals_text(t_data *data, mlx_t *mlx);
void		init_cursor_text(t_data *data, mlx_t *mlx);
void		init_door_text(t_data *data, mlx_t *mlx);
void		init_hud_text(t_data *data, mlx_t *mlx);
void		init_portalgun_text(t_data *data, mlx_t *mlx);
void		init_gun_text(t_data *data, mlx_t *mlx);

char		*assets_portals(int i);
char		*assets_cursor(int i);
char		*assets_doors(int i);
char		*assets_hud(int i);

int			parsing(char *map_name, t_data *data);
void		check_enemy(t_data *data);
void		get_infos(int fd, t_data *data);

void		free_all(char *str, int out, t_data *data);
void		free_smap(mlx_t *mlx, t_map *map);

void		close_window(void *gdata);
void		resize_window(int32_t width, int32_t height, void *gdata);
void		hook(void *data);
void		change_map(t_data *data, int np);
void		menu(t_data *data);
void		menu_events(mlx_key_data_t key, void *gdata);
void		show_menu(t_data *data, bool show);
void		portals(mouse_key_t b, action_t act, modifier_key_t mod, void *dt);
void		reset_portal(t_data *data);
int			check_portal(t_data *data, int x, int y, t_vector v);
void		shoot_portal(t_data *data, int type, int other);
void		shoot(t_data *data);
void		scroll(double xdelta, double ydelta, void *gdata);
void		mouse_move(void *gdata);
float		angle(double ux, double uy, double vx, double vy);
void		move(t_data *data);

void        door_event(t_data *data);

#endif // CUB3D_BONUS_H
