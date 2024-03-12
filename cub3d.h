/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:22:41 by vilibert          #+#    #+#             */
/*   Updated: 2024/03/11 19:12:21 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

typedef	struct s_player
{
	double	x;
	double	y;
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
