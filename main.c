/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:41:39 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/15 19:35:25 by hapryl           ###   ########.fr       */
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
    int	    map[10][19];
    int         square;
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
		while (j < x2)
		{
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
        data->player.angle -= 0.1;
    else if (keycode == 124)
        data->player.angle += 0.1;        
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
    ft_mlx_draw_rectangle(data, 0, 0, 1920, 1080, 0x00000000);
    //Map
    ft_mlx_draw_map(data);
    //Player
    ft_mlx_draw_rectangle(data, data->player.position.x - 5, data->player.position.y - 5, data->player.position.x + 5, data->player.position.y + 5, 0x00FF0000);
    //Vzor
    float   x, y;
    double	angle = data->player.angle - M_PI_4;
    while(angle < data->player.angle + M_PI_4)
    {
        for (float c = 0; c < 2000; c+=.05)
        {
            x = data->player.position.x + c*cos(angle);
            y = data->player.position.y + c*sin(angle);
            if (data->map[(int)(y/data->square)][(int)(x/data->square)] != 0)
            {
                printf("x = %f\ny = %f\n%d\n\n", x, y, data->map[(int)(y/data->square)][(int)(x/data->square)]);
                break;
            }
            my_mlx_pixel_put(data, x, y, 0x0000FF00);
        }
        angle += 0.005;
    }
    //my_mlx_pixel_put(data, x, y, 0x0000FF00);
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

    for (int y = 0; y < 10; y++)
        for (int x = 0; x < 19; x++)
            data.map[y][x] = map[y][x];
    data.square = 100;
    data.player.position.x = 500;
    data.player.position.y = 500;
    data.player.angle = 0;
    data.player.speed = 10;
    data.mlx = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
    data.img = mlx_new_image(data.mlx, 1920, 1080);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
                                 &data.endian);

    mlx_hook(data.mlx_win, 2, 1L<<0, key_hook, &data);
    mlx_loop(data.mlx);

	return (0);
}
