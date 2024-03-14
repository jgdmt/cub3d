/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:12:11 by vilibert          #+#    #+#             */
/*   Updated: 2024/03/14 11:43:28 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# include <sys/time.h>

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	correct_color(u_int8_t *pixel)
{
	int	rgba;

	rgba = 0;
	rgba += pixel[0] << 24;
	rgba += pixel[1] << 16;
	rgba += pixel[2] << 8;
	rgba += pixel[3];
	return (rgba);
}

void	ray_to_img(t_data *data, t_raycast *rc)
{
	double	step;
	double	tex_pos;
	int		y;

	step = 1.0 * data->map->no->height / rc->line_height;
	tex_pos = (rc->draw_start - data->height / 2 + rc->line_height / 2) * step;
	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		rc->tex.y = (int)tex_pos & (data->map->no->height - 1);
		tex_pos += step;
		u_int32_t color = correct_color((u_int8_t*)&((u_int32_t*)data->map->no->pixels)[data->map->no->width * rc->tex.y + (data->map->no->width - rc->tex.x - 1)]);
		if (rc->side == 1)
			color = (color >> 1) & 8355711;
		mlx_put_pixel(data->img, rc->x, y, color);
		y++;
	}
}

void	raycast(t_data *data)
{
	t_raycast rc;
	// data->player->dir.x = -1; //temp
	// data->player->dir.y = 0; //temp
	// data->player->plane.x = 0; //temp
	// data->player->plane.y = 0.66; //temp

	data->width = WIDTH; // a deplacer
	data->height = HEIGHT;
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * sizeof(int32_t));
	rc.x = 0;
	while (rc.x < data->width)
	{
		double	cameraX = 2 * rc.x / (double) data->width - 1;
		double	rayDirX = data->player->dir.x + data->player->plane.x * cameraX;
		double	rayDirY = data->player->dir.y  + data->player->plane.y * cameraX;
		t_int_vector ipos; // old mapX and mapY
		ipos.x = (int)data->player->pos.x;
		ipos.y = (int)data->player->pos.y;

		t_vector	sideDist;

      double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      t_int_vector step;

      int hit = 0; //was there a wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        step.x = -1;
        sideDist.x = (data->player->pos.x - ipos.x) * deltaDistX;
      }
      else
      {
        step.x = 1;
        sideDist.x = (ipos.x + 1.0 - data->player->pos.x) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        step.y = -1;
        sideDist.y = (data->player->pos.y - ipos.y) * deltaDistY;
      }
      else
      {
        step.y = 1;
        sideDist.y = (ipos.y + 1.0 - data->player->pos.y) * deltaDistY;
      }
      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDist.x < sideDist.y)
        {
          sideDist.x += deltaDistX;
          ipos.x += step.x;
          rc.side = 0;
        }
        else
        {
          sideDist.y += deltaDistY;
          ipos.y += step.y;
          rc.side = 1;
        }
        //Check if ray has hit a wall
        if(data->map->map[ipos.y][ipos.x] == '1') hit = 1;
      }
      if(rc.side == 0) perpWallDist = (sideDist.x - deltaDistX);
      else          perpWallDist = (sideDist.y - deltaDistY);

      //Calculate height of line to draw on screen
      rc.line_height = (int)(data->height / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      rc.draw_start = - rc.line_height / 2 + data->height/ 2;
      if(rc.draw_start < 0) rc.draw_start = 0;
      rc.draw_end = rc.line_height / 2 + data->height/ 2;
      if(rc.draw_end >= data->height) rc.draw_end = data->height- 1;


 //texturing calculations
    //   int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (rc.side == 0) wallX = data->player->pos.y + perpWallDist * rayDirY;
      else           wallX = data->player->pos.x + perpWallDist * rayDirX;
      wallX -= floor((wallX));
 //x coordinate on the texture
      rc.tex.x = (int)(wallX * (double)(data->map->no->width));
      if(rc.side == 0 && rayDirX > 0) rc.tex.x = data->map->no->width - rc.tex.x - 1;
      if(rc.side == 1 && rayDirY < 0) rc.tex.x = data->map->no->width - rc.tex.x - 1;
     ray_to_img(data, &rc);
	(rc.x)++;
    }
    mlx_image_to_window(data->mlx, data->img, 0, 0);
}
