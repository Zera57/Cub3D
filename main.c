/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:41:39 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/20 19:25:20 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_mms_20200219/mlx.h"
#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_data {
    void		*mlx;
    void		*mlx_win;
    void		*img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    t_player    player;
    int	        map[10][19];
    int         square;
    t_settings	*settings;
    const size_t rect_w;
    const size_t rect_h;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void            ft_mlx_draw_rectangle(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	int		i;
	int		j;

	i = y1;
	while (i < y2)
	{
		j = x1;
		while (j <= x2)
		{
            //printf("x = %d, y = %d", j, i);
			my_mlx_pixel_put(data, j, i, color);
			j++;
		}
		i++;
	}

}

int	            ft_mlx_draw_map(t_data *data)
{
    int y = 0;

    while (y < 10)
    {
        int x = 0;
        while (x < 19)
        {
            if (data->map[y][x])
                ft_mlx_draw_rectangle(data, x * data->square, y * data->square, x * data->square + data->square, y * data->square + data->square, 0x000000FF);
            x++;
        }
        y++;
    }
    return (0);
}

int	            key_move(t_data *data, int keycode)
{
    int     delta_x, delta_y;
    if (keycode == 123)
    {
        data->player.angle += 0.1;
        double oldDirX = data->player.dir.x;
        data->player.dir.x = data->player.dir.x * cos(1) - data->player.dir.y * sin(1);
        data->player.dir.y = oldDirX * sin(1) + data->player.dir.y * cos(1);
        double oldPlaneX = data->player.planeX;
        data->player.planeX = data->player.planeX * cos(1) - data->player.planeY * sin(1);
        data->player.planeY = oldPlaneX * sin(1) + data->player.planeY * cos(1);
    }
    else if (keycode == 124)
    {
        data->player.angle += 0.1;
        double oldDirX = data->player.dir.x;
        data->player.dir.x = data->player.dir.x * cos(-1) - data->player.dir.y * sin(-1);
        data->player.dir.y = oldDirX * sin(-1) + data->player.dir.y * cos(-1);
        double oldPlaneX = data->player.planeX;
        data->player.planeX = data->player.planeX * cos(-1) - data->player.planeY * sin(-1);
        data->player.planeY = oldPlaneX * sin(-1) + data->player.planeY * cos(-1);
    }
    else if (keycode == 125)
    {
        data->player.position.x = data->player.position.x - data->player.speed * cos(data->player.angle);
        data->player.position.y = data->player.position.y - data->player.speed * sin(data->player.angle);
    }
    else if (keycode == 126)
    {
        data->player.position.x = data->player.position.x + data->player.speed * cos(data->player.angle);
        data->player.position.y = data->player.position.y + data->player.speed * sin(data->player.angle);
    }
    //Zachistka
    ft_mlx_draw_rectangle(data, 0, 0, data->settings->R1, data->settings->R2, data->settings->F);
    //Vzor
#pragma region Raycasting DDA with normals
    // //which box of the map we're in
    // int mapX = int(posX);
    // int mapY = int(posY);

    // //length of ray from current position to next x or y-side
    // double sideDistX;
    // double sideDistY;

    // //length of ray from one x or y-side to next x or y-side
    // double deltaDistX = std::abs(1 / rayDirX);
    // double deltaDistY = std::abs(1 / rayDirY);
    // double perpWallDist;

    // //what direction to step in x or y-direction (either +1 or -1)
    // int stepX;
    // int stepY;

    // int hit = 0; //was there a wall hit?
    // int side; //was a NS or a EW wall hit?
#pragma endregion
#pragma region Testing Raycasting
    int	    mx, my, mp;
    float   x, y, xo, yo;
    double fov = M_PI/3;
    for (size_t i=1; i < data->settings->R1; i++) 
    {
        double cameraX = 2 * i / data->settings->R1; //i-coordinate in camera space
        double rayDirX = data->player.dir.x + data->player.planeX*cameraX;
        double rayDirY = data->player.dir.y + data->player.planeY*cameraX;

        //which box of the map we're in
        int mapX = (int)data->player.position.x;
        int mapY = (int)data->player.position.y;

        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        //length of ray from one x or y-side to next x or y-side
        double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
        double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
        double perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?

        //calculate step and initial sideDist
        if (rayDirX < 0)
        {
        stepX = -1;
        sideDistX = (data->player.position.x - mapX) * deltaDistX;
        }
        else
        {
        stepX = 1;
        sideDistX = (mapX + 1.0 - data->player.position.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
        stepY = -1;
        sideDistY = (data->player.position.y - mapY) * deltaDistY;
        }
        else
        {
        stepY = 1;
        sideDistY = (mapY + 1.0 - data->player.position.y) * deltaDistY;
        }

            //perform DDA
        while (hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (data->map[mapX][mapY] > 0) hit = 1;
        }

        //Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
        if (side == 0) perpWallDist = (mapX - data->player.position.x + (1 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - data->player.position.y + (1 - stepY) / 2) / rayDirY;

        //Calculate height of line to draw on screen
        int lineHeight = (int)(data->settings->R2 / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + data->settings->R2 / 2;
        if(drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + data->settings->R2 / 2;
        if(drawEnd >= data->settings->R2) drawEnd = data->settings->R2 - 1;
        printf("lineH = %d\n", lineHeight);
        ft_mlx_draw_rectangle(data, i, drawStart, i, drawEnd, 0x00FFFFFF);
    }

#pragma endregion
#pragma region Working Raycasting 
    // float   x, y;
    // double fov = M_PI/3;
    // for (size_t i=0; i < data->settings->R1; i++) 
    // {
    //     float angle = data->player.angle - fov / 2 + fov * i / data->settings->R1;
    //     for (float c = 0; c < 20; c+=.005)
    //     {
    //         x = data->player.position.x + c*cos(angle);
    //         y = data->player.position.y + c*sin(angle);
    //         if (data->map[(int)(y)][(int)(x)] != 0)
    //         {
    //             int wallH = data->settings->R2 / (c * cos(data->player.angle - angle));
    //             if (wallH > data->settings->R2) wallH = data->settings->R2;
    //             ft_mlx_draw_rectangle(data, i, data->settings->R2/2 - wallH/2, i, data->settings->R2/2 + wallH/2, 0x00FFFFFF);            
    //             break;
    //         }
    //         my_mlx_pixel_put(data, x * data->square, y * data->square, 0x0000FF00);
    //         size_t pix_x = x*data->square*4;
    //         size_t pix_y = y*data->square*4;
    //     }
    // }
#pragma endregion
    //Map
    ft_mlx_draw_map(data);
    //Player
    ft_mlx_draw_rectangle(data, data->player.position.x * data->square - 5, data->player.position.y * data->square - 5, data->player.position.x * data->square + 5, data->player.position.y * data->square + 5, 0x00FF0000);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
    return (0);
}

int	            key_esc(t_data *data)
{
    mlx_destroy_window(data->mlx, data->mlx_win);
    exit(1);
}

int             key_hook(int keycode, t_data *img)
{
    //printf("%d", keycode);
    if ((keycode >= 123 && keycode <= 126))
        key_move(img, keycode);
    if (keycode == 53)
        key_esc(img);
    return (0);
}

void f(void *s)
{
    printf("%s\n", s);
}

int             main(void)
{
    t_data      data;
    int	    map[10][19] = {     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,0,0,0,0,1,1,1,1,0,1,1,1,0,0,0,1,0,1},
                                {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1},
                                {1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
                                {1,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,1,0,1},
                                {1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
                                };


    data.settings = get_settings("/Users/hapryl/Desktop/Projects/cub3d/my_git/settings.cub");
    //ft_lstiter(data.settings->map, &f);
    for (int y = 0; y < 10; y++)
        for (int x = 0; x < 19; x++)
            data.map[y][x] = map[y][x];
    data.square = 25;
    data.player.position.x = 10;
    data.player.position.y = 5;
    data.player.angle = 0;
    data.player.dir.x = 0.5;
    data.player.dir.y = 0.5;
    data.player.planeX = 0;
    data.player.planeY = 0.66;
    data.player.speed = 0.1;
    data.mlx = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx, data.settings->R1, data.settings->R2, "Hello world!");
    data.img = mlx_new_image(data.mlx, data.settings->R1, data.settings->R2);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
                                 &data.endian);
    mlx_hook(data.mlx_win, 2, 1L<<0, key_hook, &data);
    mlx_loop(data.mlx);
	return (0);
}
