/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:12:11 by vilibert          #+#    #+#             */
/*   Updated: 2024/03/13 17:44:07 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

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
// void	test(t_data *data, )
// {
//  		double step = 1.0 * data->map->no->height / lineHeight;
//       // Starting texture coordinate
//       double texPos = (drawStart - data->height / 2 + lineHeight / 2) * step;
// 	  int y;
// 	  y = drawStart;
	  
//       while(y < drawEnd)
//       {
//         // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
//         int texY = (int)texPos & (data->map->no->height - 1);
//         texPos += step;
//         u_int32_t color = correct_color((u_int8_t*)&((u_int32_t*)data->map->no->pixels)[data->map->no->width * texY + (data->map->no->width - texX - 1)]);
//         //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
//         if(side == 1) color = (color >> 1) & 8355711;
//         mlx_put_pixel(data->img, x, y, color);
// 		y++;
//       }
// }

void	raycast(t_data *data)
{
	// data->player->pos.x = 22; //temp
	// data->player->pos.y = 12; //temp
	data->player->dir.x = -1; //temp
	data->player->dir.y = 0; //temp
	data->player->plane.x = 0; //temp
	data->player->plane.y = 0.66; //temp

	data->width = WIDTH; // a deplacer
	data->height = HEIGHT;
	int x;
	x = 0;
	while (x < data->width)
	{
		double	cameraX = 2 * x / (double) data->width - 1;
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
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDist.x = (data->player->pos.x - ipos.x) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDist.x = (ipos.x + 1.0 - data->player->pos.x) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDist.y = (data->player->pos.y - ipos.y) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDist.y = (ipos.y + 1.0 - data->player->pos.y) * deltaDistY;
      }
      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDist.x < sideDist.y)
        {
          sideDist.x += deltaDistX;
          ipos.x += stepX;
          side = 0;
        }
        else
        {
          sideDist.y += deltaDistY;
          ipos.y += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(data->map->map[ipos.y][ipos.x] == '1') hit = 1;
      }
      if(side == 0) perpWallDist = (sideDist.x - deltaDistX);
      else          perpWallDist = (sideDist.y - deltaDistY);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(data->height / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + data->height/ 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + data->height/ 2;
      if(drawEnd >= data->height) drawEnd = data->height- 1;


 //texturing calculations
    //   int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) wallX = data->player->pos.y + perpWallDist * rayDirY;
      else           wallX = data->player->pos.x + perpWallDist * rayDirX;
      wallX -= floor((wallX));
 //x coordinate on the texture
      int texX = (int)(wallX * (double)(data->map->no->width));
      if(side == 0 && rayDirX > 0) texX = data->map->no->width - texX - 1;
      if(side == 1 && rayDirY < 0) texX = data->map->no->width - texX - 1;
      //draw the pixels of the stripe as a vertical line
	              // How much to increase the texture coordinate per screen pixel
     	double step = 1.0 * data->map->no->height / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - data->height / 2 + lineHeight / 2) * step;
	  int y;
	  y = drawStart;
	  
      while(y < drawEnd)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (data->map->no->height - 1);
        texPos += step;
        u_int32_t color = correct_color((u_int8_t*)&((u_int32_t*)data->map->no->pixels)[data->map->no->width * texY + (data->map->no->width - texX - 1)]);
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
        mlx_put_pixel(data->img, x, y, color);
		y++;
      }
	x++;
    }
    mlx_image_to_window(data->mlx, data->img, 0, 0);
}
