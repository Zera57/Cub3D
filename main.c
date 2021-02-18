/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:41:39 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/18 20:05:07 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	if (x >= 0 && y >= 0 && x < data->settings.R1 && y < data->settings.R2 && color < 0xFF000000)
	{
		dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

unsigned int	my_mlx_get_color(t_img *img, int x, int y)
{
	unsigned int	color;

	color = 0x008a66e5;
	if (x >= 0 && y >= 0 && x <= img->width && y <= img->height)
		color = *(unsigned int*)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)));
	return (color);
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

void            ft_mlx_draw_picture(t_data *data, t_point start, t_dpoint offset, double wallH, double dist)
{
	double			x_texture;
	double			y_texture;
	int				y_temp;
	unsigned int	color;

	x_texture = 0;
	y_temp = start.y;
	if (start.y < 0)
	{
		y_texture = (offset.y * wallH / 2) - (offset.y * data->settings.R2 / 2);
		start.y = 0;
	}
	while (data->sprite.width > x_texture)
	{
		if (data->rays[start.x] > dist)
		{
			start.y = y_temp;
			y_texture = 0;
			while (data->sprite.height > y_texture)
			{
				color = my_mlx_get_color(&data->sprite, (int)x_texture, (int)y_texture);
					my_mlx_pixel_put(data, start.x, start.y, color);
				start.y++;
				y_texture += offset.y; 
			}
		}
		start.x++;
		x_texture += offset.x; 
	}
}

void            ft_mlx_draw_wall(t_data *data, int x, int wallH, char c)
{
	int				y;
	int				id_texture;
	double			x_texture;
	double			y_texture;
	double			yo;
	unsigned int	color;

	y = data->settings.R2 / 2 - wallH/2;
	y_texture = 0;
	if (c == 'n')
	{
		x_texture = ((int)data->wall_point.x % data->bit) / ((double)data->bit / (double)data->textures[0].width);
		id_texture = 0;
		yo = (double)data->textures[0].height / wallH;
	}
	if (c == 's')
	{
		x_texture = ((int)data->wall_point.x % data->bit) / ((double)data->bit / (double)data->textures[1].width);
		id_texture = 1;
		yo = (double)data->textures[1].height / wallH;
	}
	if (c == 'w')
	{
		x_texture = ((int)data->wall_point.y % data->bit) / ((double)data->bit / (double)data->textures[2].width);
		id_texture = 2;
		yo = (double)data->textures[2].height / wallH;
	}
	if (c == 'e')
	{
		x_texture = ((int)data->wall_point.y % data->bit) / ((double)data->bit / (double)data->textures[3].width);
		id_texture = 3;
		yo = (double)data->textures[3].height / wallH;
	}
	if (y < 0)
	{
		y_texture = (yo * wallH / 2) - (yo * data->settings.R2 / 2);
		y = 0;
	}
	while (y < data->settings.R2 && y_texture < data->textures[id_texture].height)
	{
		color = my_mlx_get_color(&data->textures[id_texture], (int)x_texture, (int)y_texture);
		my_mlx_pixel_put(data, x, y, color);
		y++;
		y_texture += yo; 
	}
}

void            ft_mlx_draw_sprites(t_data *data)
{
	t_list		*temp;
	t_dpoint	*s;

	temp = data->list_s;
	while (temp != NULL)
	{
		s = temp->content;

		double sprite_dir = atan2(s->y - data->player.position.y, s->x - data->player.position.x);

		while (sprite_dir - data->player.angle >  M_PI) sprite_dir -= 2*M_PI; 
		while (sprite_dir - data->player.angle < -M_PI) sprite_dir += 2*M_PI;
		double min = data->player.angle - M_PI/2;
		double max = data->player.angle + M_PI/2;
		while (min <  0) min += 2*M_PI; 
		while (max > 2*M_PI) max -= 2*M_PI;
		if ((sprite_dir > min && sprite_dir < max) || (sprite_dir > min && sprite_dir > max) || (sprite_dir < min && sprite_dir < max))
		{
			double sprite_dist = fabs(fabs(s->y - data->player.position.y) / sin(sprite_dir));
			
			int		wallH = data->settings.R2 / (sprite_dist / data->bit);

			int x = (sprite_dir - data->player.angle + data->player.fov / 2) * data->settings.R1 / data->player.fov - wallH / 2;
			int y = data->settings.R2 / 2 - wallH / 2;

			if (x + wallH > 0 && x - wallH < data->settings.R1)
				ft_mlx_draw_picture(data, (t_point){x, y}, (t_dpoint){(double)data->sprite.width / wallH, (double)data->sprite.height / wallH}, wallH, sprite_dist);
		}
		temp = temp->next;
	}
}

void			ft_sort_sprites(t_data *data)
{
	int		i;
	t_list	*temp1;
	t_list	*temp2;

	i = 0;
	while (i < ft_lstsize(data->list_s))
	{
		i++;
		temp1 = data->list_s;
		// while ()
	}
}

int				ft_mlx_draw_map(t_data *data)
{
	int x, y = 0;

	while (y < data->map.height)
	{
		x = 0;
		while (data->map.map[y][x] != '\0')
		{
			if (data->map.map[y][x] == '1')
			{	ft_mlx_draw_rectangle(data, x * data->square, y * data->square, x * data->square + data->square, y * data->square + data->square, 0x000000FF);	}
			if (data->map.map[y][x] == '2')
			{	ft_mlx_draw_rectangle(data, x * data->square, y * data->square, x * data->square + data->square, y * data->square + data->square, 0x00e4d720);	}
			x++;
		}
		y++;
	}
	return (0);
}

int	            key_move(t_data *data, int keycode)
{
	double	x, y;
	int     delta_x, delta_y;
	if (keycode == 123)
	{
		if (data->player.angle <= 0)
			data->player.angle = 2*M_PI;
		data->player.angle -= 0.05;
	}
	else if (keycode == 124)
	{
		if (data->player.angle >= 2 * M_PI)
			data->player.angle = 0;
		data->player.angle += 0.05;
	}
	else if (keycode == 125)
	{
		x = data->player.position.x - data->player.speed * cos(data->player.angle);
		y = data->player.position.y - data->player.speed * sin(data->player.angle);
		if (data->map.map[(int)(data->player.position.y /data->bit)][(int)x/data->bit] != '1')
			data->player.position.x = x;
		if (data->map.map[(int)y/data->bit][(int)data->player.position.x/data->bit] != '1')
			data->player.position.y = y;
	}
	else if (keycode == 126)
	{
		x = data->player.position.x + data->player.speed * cos(data->player.angle);
		y = data->player.position.y + data->player.speed * sin(data->player.angle);
		if (data->map.map[(int)(data->player.position.y/data->bit)][(int)(x/data->bit)] != '1')
			data->player.position.x = x;
		if (data->map.map[(int)(y/data->bit)][(int)(data->player.position.x/data->bit)] != '1')
			data->player.position.y = y;
	}
	//Ceiling
	ft_mlx_draw_rectangle(data, 0, 0, data->settings.R1, data->settings.R2/2, data->settings.C);
	//Floor
	ft_mlx_draw_rectangle(data, 0, data->settings.R2/2+1, data->settings.R1, data->settings.R2, data->settings.F);
	//Map
	ft_mlx_draw_map(data);
	//Vzor
#pragma region Working Raycasting 
	double	rx, ry, xo, yo, dist;
	int	    wallH = 0;


	for (size_t i=0; i < data->settings.R1; i++) 
	{
		float angle = data->player.angle - data->player.fov / 2 + data->player.fov * i / data->settings.R1;
		if (angle <= 0)
			angle += 2 * M_PI;
		if (angle > 2 * M_PI)
			angle -= 2 * M_PI;
		wallH = 0;
		double distH, distV;
		int dof = 0;
		char            side ;
	
		if (angle > M_PI)
			side = 'n';
		else
			side = 's';
		distH = fabs(get_Horizontal_dist(data, angle));
		distV = fabs(get_Vertical_dist(data, angle));
		if (distV < distH)
		{
			if (angle < M_PI / 2 || angle > M_PI * 3 / 2)
				side = 'e';
			else
				side = 'w';
			distH = distV;
		}
		data->rays[i] = distH;
		wallH = data->settings.R2 / (distH / data->bit * cos(data->player.angle - angle));

		wallH = abs(wallH);
		// if (wallH > data->settings.R2)
		// 	wallH = data->settings.R2;
		
		ft_mlx_draw_wall(data, i, wallH, side);
		//ft_mlx_draw_rectangle(data, i, data->settings.R2/2 - wallH/2, i, data->settings.R2/2 + wallH/2, color);
		
		// for (float c = 0; c < 20; c+=.005)
		// {
		//     x = data->player.position.x + c*cos(angle);
		//     y = data->player.position.y + c*sin(angle);
			
		//     if (data->map.map[(int)(y)][(int)(x)] != 0)
		//     {
		//         int wallH = data->settings.R2 / (c * cos(data->player.angle - angle));
		//         if (wallH > data->settings.R2) wallH = data->settings.R2;
		//         ft_mlx_draw_rectangle(data, i, data->settings.R2/2 - wallH/2, i, data->settings.R2/2 + wallH/2, 0x00FFFFFF);            
		//         break;
		//     }
		//     my_mlx_pixel_put(data, x * data->square, y * data->square, 0x0000FF00);
		// }
	}
#pragma endregion
	//Sprites
	ft_mlx_draw_sprites(data);
	//Player
	ft_mlx_draw_rectangle(data, data->player.position.x /data->bit * data->square - data->square/5, data->player.position.y /data->bit * data->square - data->square/5, data->player.position.x /data->bit * data->square + 5, data->player.position.y /data->bit * data->square + 5, 0x00FF0000);
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
	if ((keycode != 53))
		key_move(img, keycode);
	if (keycode == 53)
		key_esc(img);
	return (0);
}

void f(void *s)
{
	printf("|%s|\n", s);
}

void tester_parsing(t_data *data)
{
	printf("R %d %d\n", data->settings.R1, data->settings.R2);
	printf("F 0 = %d\nC 2BA5F0 = %X\n\n", data->settings.F, data->settings.C);
	printf("-----------------------------------\n");
	ft_lstiter(data->settings.map, &f);
	printf("-------------------------------\n");
	error("All good");
}

int             main(void)
{
	t_data      data;
	// int	    map[10][19] = {     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	// 							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 							{1,0,0,0,0,1,1,1,1,0,1,1,1,0,0,0,1,0,1},
	// 							{1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,2,0,1},
	// 							{1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,2,0,1},
	// 							{1,0,0,0,0,0,0,0,0,0,0,0,1,0,2,0,2,0,1},
	// 							{1,0,0,0,0,1,2,1,1,1,1,0,1,0,2,0,1,0,1},
	// 							{1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,1},
	// 							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
								// };

	data.mlx = mlx_init();
	get_settings(&data, "/Users/hapryl/Desktop/Projects/cub3d/my_git/settings.cub");
	data.mlx_win = mlx_new_window(data.mlx, data.settings.R1, data.settings.R2, "Hello world!");
	data.img.img = mlx_new_image(data.mlx, data.settings.R1, data.settings.R2);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, &data.img.line_length,
								&data.img.endian);

	mlx_put_image_to_window(data.mlx, data.mlx_win, data.textures[0].img, 0, 0);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.textures[1].img, 0, 64);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.textures[2].img, 0, 128);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.textures[3].img, 0, 192);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.sprite.img, data.settings.R1 / 2, 0);

	// tester_parsing(&data);

	// for (int y = 0; y < 10; y++)
	// 	for (int x = 0; x < 19; x++)
	// 		data.map[y][x] = map[y][x];
	data.square = 10;
	data.bit = 32;
	data.player.fov = M_PI/3;
	data.player.angle = M_PI / 2;
	data.player.dir.x = 0.5;
	data.player.dir.y = 0.5;
	data.player.planeX = 0;
	data.player.planeY = 0.66;
	data.player.speed = 0.1 * data.bit;
	data.rays = malloc(sizeof(double) * data.settings.R1);

	//huita
	int y = 0;

	while(y < data.map.height)
	{
		int x = 0;
		while(x < data.map.width)
		{
			if (data.map.map[y][x] == '2')
			{
				t_dpoint	*p = malloc(sizeof(t_dpoint));
				p->x = (x + 0.5) * data.bit;
				p->y = (y + 0.5) * data.bit;
				if (!data.list_s)
					data.list_s = ft_lstnew(p);
				else
					ft_lstadd_front(&data.list_s, ft_lstnew(p));
			}
			if (data.map.map[y][x] == 'N' || data.map.map[y][x] == 'S' || data.map.map[y][x] == 'W' || data.map.map[y][x] == 'E')
			{
				validate_map(&data, x, y);
				data.player.position.x = (x + 0.5) * data.bit;
				data.player.position.y = (y + 0.5) * data.bit;
			}
			x++;
		}
		y++;
	}

	mlx_hook(data.mlx_win, 2, 1L<<0, key_hook, &data);
	mlx_loop(data.mlx);
	// key_move(&data, 0);
	return (0);
}
