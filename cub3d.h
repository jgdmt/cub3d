/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:22:41 by vilibert          #+#    #+#             */
/*   Updated: 2024/03/11 12:07:45 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_map
{
	char	**map;
	void	*no_texture;
	void	*so_texture;
	void	*we_texture;
	void	*ea_texture;
	int		floor_color;
	int		ceiling_color;
}	t_map;

typedef struct s_data
{
	
}	t_data;

void raycast_test(void);


#endif // CUB3D_H
