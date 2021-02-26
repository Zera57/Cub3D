/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:41:39 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/25 19:34:32 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void            ft_mlx_draw_picture(t_data *data, t_point start, t_dpoint offset, double wallH, double dist)
{
	double			x_texture;
	double			y_texture;
	double			y_texture_temp;
	int				y_temp;
	unsigned int	color;

	x_texture = 0;
	y_texture = 0;
	if (start.y < 0)
	{
		start.y = 0;
		y_texture = (offset.y * wallH / 2) - (offset.y * data->settings.R2 / 2);
	}
	y_temp = start.y;
	y_texture_temp = y_texture;
	while (data->sprite.width > x_texture)
	{
		if (data->rays[start.x] > dist)
		{
			start.y = y_temp;
			y_texture = y_texture_temp;
			while (start.y <= data->settings.R2 && data->sprite.height > y_texture)
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


void			ft_get_distance_sprites(t_data *data)
{
	t_list	*temp;

	temp = data->list_s;
	while (temp)
	{
		((t_dpoint*)temp->content)->angle = atan2(((t_dpoint*)temp->content)->y - data->player.position.y, ((t_dpoint*)temp->content)->x - data->player.position.x);
		while (((t_dpoint*)temp->content)->angle - data->player.angle >  M_PI) ((t_dpoint*)temp->content)->angle -= 2*M_PI; 
		while (((t_dpoint*)temp->content)->angle - data->player.angle < -M_PI) ((t_dpoint*)temp->content)->angle += 2*M_PI;
		((t_dpoint*)temp->content)->dist = fabs(fabs(((t_dpoint*)temp->content)->y - data->player.position.y) / sin(((t_dpoint*)temp->content)->angle));;
		temp = temp->next;
	}
}

void			ft_sort_sprites(t_data *data)
{
	void	*c;
	t_list	*temp;

	ft_get_distance_sprites(data);
	temp = data->list_s;
	while (temp && temp->next)
	{
		if (((t_dpoint*)temp->content)->dist < ((t_dpoint*)temp->next->content)->dist)
		{
			c = temp->content;
			temp->content = temp->next->content;
			temp->next->content = c;
		}
		temp = temp->next;
	}
}

void            ft_mlx_draw_sprites(t_data *data)
{
	t_point		p;
	t_list		*temp;

	ft_sort_sprites(data);
	temp = data->list_s;
	while (temp != NULL)
	{
		double min = data->player.angle - M_PI/2;
		double max = data->player.angle + M_PI/2;
		while (min <  0) min += 2*M_PI; 
		while (max > 2*M_PI) max -= 2*M_PI;
		if ((((t_dpoint*)temp->content)->angle > min && ((t_dpoint*)temp->content)->angle < max) || (((t_dpoint*)temp->content)->angle > min && ((t_dpoint*)temp->content)->angle > max) || (((t_dpoint*)temp->content)->angle < min && ((t_dpoint*)temp->content)->angle < max))
		{
			int		wallH = data->settings.R2 / (((t_dpoint*)temp->content)->dist / data->bit);
			p.x = (((t_dpoint*)temp->content)->angle - data->player.angle + data->player.fov / 2) * data->settings.R1 / data->player.fov - wallH / 2;
			p.y = data->settings.R2 / 2 - wallH / 2;

			if (p.x + wallH > 0 && p.x - wallH < data->settings.R1)
				ft_mlx_draw_picture(data, p, (t_dpoint){(double)data->sprite.width / wallH, (double)data->sprite.height / wallH}, wallH, ((t_dpoint*)temp->content)->dist);
		}
		temp = temp->next;
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
	if (keycode == 13)
		key_w(data);
	else if (keycode == 0)
		key_a(data);
	else if (keycode == 1)
		key_s(data);
	else if (keycode == 2)
		key_d(data);
	else if (keycode == 123)
		key_l(data);
	else if (keycode == 124)
		key_r(data);
	//Ceiling
	ft_mlx_draw_rectangle(data, 0, 0, data->settings.R1, data->settings.R2/2, data->settings.C);
	//Floor
	ft_mlx_draw_rectangle(data, 0, data->settings.R2/2+1, data->settings.R1, data->settings.R2, data->settings.F);
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
		
		ft_mlx_draw_wall(data, i, wallH, side);
	}
#pragma endregion
	//Sprites
	ft_mlx_draw_sprites(data);
	//Map
	ft_mlx_draw_map(data);
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

int             main(int arg, char **argv)
{
	t_data      data;

	data.mlx = mlx_init();
	get_settings(&data, argv[1]);
	data.mlx_win = mlx_new_window(data.mlx, data.settings.R1, data.settings.R2, "Hello world!");
	data.img.img = mlx_new_image(data.mlx, data.settings.R1, data.settings.R2);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, &data.img.line_length,
								&data.img.endian);

	// tester_parsing(&data);

	data.square = 30;
	objects_init(&data);

	key_move(&data, -1);
	if (arg == 3 && (ft_strncmp("screenshot", argv[2], 11)) == 0)
		make_screenshot(&data);
	mlx_hook(data.mlx_win, 2, 1L<<0, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
