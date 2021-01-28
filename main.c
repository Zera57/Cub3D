/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:41:39 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/28 17:51:37 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
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
        if (data->player.angle <= 0)
            data->player.angle = 2*M_PI;
        data->player.angle -= 0.1;
        double oldDirX = data->player.dir.x;
        data->player.dir.x = data->player.dir.x * cos(1) - data->player.dir.y * sin(1);
        data->player.dir.y = oldDirX * sin(1) + data->player.dir.y * cos(1);
        double oldPlaneX = data->player.planeX;
        data->player.planeX = data->player.planeX * cos(1) - data->player.planeY * sin(1);
        data->player.planeY = oldPlaneX * sin(1) + data->player.planeY * cos(1);
    }
    else if (keycode == 124)
    {
        if (data->player.angle >= 2*M_PI)
            data->player.angle = 0;
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
    //Ceiling
    ft_mlx_draw_rectangle(data, 0, 0, data->settings->R1, data->settings->R2/2, data->settings->C);
    //Floor
    ft_mlx_draw_rectangle(data, 0, data->settings->R2/2+1, data->settings->R1, data->settings->R2, data->settings->F);
    //Map
    ft_mlx_draw_map(data);
    //Vzor
#pragma region Working Raycasting 
    double	rx, ry, x, y, xo, yo, dist;
    double  fov = M_PI/3;
    int	    wallH = 0;


    for (size_t i=0; i < data->settings->R1; i++) 
    {
        float angle = data->player.angle - fov / 2 + fov * i / data->settings->R1;
        if (angle < 0)
            angle += 2 * M_PI;
        if (angle > 2 * M_PI)
            angle -= 2 * M_PI;
        wallH = 0;
        double distH, distV;
        int dof = 0;
        unsigned int color = 0x006358ab;
        
        distH = fabs(get_Horizontal_dist(data, angle));
        distV = fabs(get_Vertical_dist(data, angle));
        if (distV < distH)
        {
            distH = distV;
            color = 0x004520ab;
        }
        wallH = data->settings->R2 / (distH * cos(data->player.angle - angle));
        
        wallH = abs(wallH);
            if (wallH > data->settings->R2)
                wallH = data->settings->R2;
        ft_mlx_draw_rectangle(data, i, data->settings->R2/2 - wallH/2, i, data->settings->R2/2 + wallH/2, color);
        
        // for (float c = 0; c < 20; c+=.005)
        // {
        //     x = data->player.position.x + c*cos(angle);
        //     y = data->player.position.y + c*sin(angle);
            
        //     if (data->map[(int)(y)][(int)(x)] != 0)
        //     {
        //         int wallH = data->settings->R2 / (c * cos(data->player.angle - angle));
        //         if (wallH > data->settings->R2) wallH = data->settings->R2;
        //         ft_mlx_draw_rectangle(data, i, data->settings->R2/2 - wallH/2, i, data->settings->R2/2 + wallH/2, 0x00FFFFFF);            
        //         break;
        //     }
        //     my_mlx_pixel_put(data, x * data->square, y * data->square, 0x0000FF00);
        // }
    }
#pragma endregion
    //Player
    ft_mlx_draw_rectangle(data, data->player.position.x * data->square - 5, data->player.position.y * data->square - 5, data->player.position.x * data->square + 5, data->player.position.y * data->square + 5, 0x00FF0000);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
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
    ft_lstiter(data.settings->map, &f);
    for (int y = 0; y < 10; y++)
        for (int x = 0; x < 19; x++)
            data.map[y][x] = map[y][x];
    data.square = 25;
    data.player.position.x = 10;
    data.player.position.y = 5;
    data.player.angle = 3 * M_PI / 2;
    data.player.dir.x = 0.5;
    data.player.dir.y = 0.5;
    data.player.planeX = 0;
    data.player.planeY = 0.66;
    data.player.speed = 0.1;
    data.mlx = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx, data.settings->R1, data.settings->R2, "Hello world!");
    data.img.img = mlx_new_image(data.mlx, data.settings->R1, data.settings->R2);
    data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, &data.img.line_length,
                                 &data.img.endian);
    mlx_hook(data.mlx_win, 2, 1L<<0, key_hook, &data);
    mlx_loop(data.mlx);
	return (0);
}
