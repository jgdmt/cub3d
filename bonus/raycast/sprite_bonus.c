/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:11:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/04/26 11:34:23 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	sprite(t_data *data, t_raycast *rc)
{
	int		spriteOrder[data->map->nb_enemy];
	double	spriteDistance[data->map->nb_enemy];
	for(int i = 0; i < data->map->nb_enemy; i++)
    {
      spriteOrder[i] = i;
      spriteDistance[i] = ((rc->player.pos.x - data->map->enemies[i].pos.x) * (rc->player.pos.x - data->map->enemies[i].pos.x) + (rc->player.pos.y - data->map->enemies[i].pos.y) * (rc->player.pos.y - data->map->enemies[i].pos.y)); //sqrt not taken, unneeded
    }
    // sortSprites(spriteOrder, spriteDistance, data->map->nb_enemy);

    //after sorting the sprites, do the projection and draw them
    for(int i = 0; i < data->map->nb_enemy; i++)
    {
      //translate sprite position to relative to camera
      double spriteX = data->map->enemies[spriteOrder[i]].pos.x - rc->player.pos.x;
      double spriteY = data->map->enemies[spriteOrder[i]].pos.y - rc->player.pos.y;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      double invDet = 1.0 / ((rc->player.plane.x * rc->player.dir.y) - (rc->player.dir.x * rc->player.plane.y)); //required for correct matrix multiplication
      double transformX = invDet * (rc->player.dir.y * spriteX - rc->player.dir.x * spriteY);
      double transformY = invDet * (-rc->player.plane.y * spriteX + rc->player.plane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
      int spriteScreenX = (int)((data->width / 2) * (1 + transformX / transformY));
		printf("%lf\n", transformY);
      #define uDiv 1
      #define vDiv 1
      #define vMove 0.0
      int vMoveScreen = (int)(vMove / transformY) + rc->player.pitch + rc->player.posz / transformY;

      //calculate height of the sprite on screen
      int spriteHeight = abs((int)(data->height / (transformY))) / vDiv; //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + data->height / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + data->height / 2 + vMoveScreen;
      if(drawEndY >= data->height) drawEndY = data->height - 1;

      //calculate width of the sprite
      int spriteWidth = abs( (int)(data->width / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= data->width) drawEndX = data->width - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * data->map->en_sprites[0]->width / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < data->width && transformY < rc->z_buff_x[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y - vMoveScreen) * 256 - data->height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * data->map->en_sprites[0]->height) / spriteHeight) / 256;
          uint32_t color = correct_color((u_int8_t *)&(((uint32_t *)data->map->en_sprites[0]->pixels)[data->map->en_sprites[0]->width * texY + texX])); //get current color from the texture
          if(color)
		  	data->buff[(y * data->width) + stripe] = color; 
        }
      }
    }
}
