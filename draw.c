/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zera <zera@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 23:12:32 by zera              #+#    #+#             */
/*   Updated: 2021/02/25 23:19:14 by zera             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ft_mlx_draw_wall(t_data *data, int x, int wallH, char c)
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

void	ft_mlx_draw_walls(t_data *data)
{
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
}

void	draw(t_data *data)
{
	//Ceiling
	ft_mlx_draw_rectangle(data, 0, 0, data->settings.R1, data->settings.R2/2, data->settings.C);
	//Floor
	ft_mlx_draw_rectangle(data, 0, data->settings.R2/2+1, data->settings.R1, data->settings.R2, data->settings.F);
	//Vzor
	ft_mlx_draw_walls(data);
	//Sprites
	ft_mlx_draw_sprites(data);
	//Map
	ft_mlx_draw_map(data);
	//Player
	ft_mlx_draw_rectangle(data, data->player.position.x /data->bit * data->square - data->square/5, data->player.position.y /data->bit * data->square - data->square/5, data->player.position.x /data->bit * data->square + 5, data->player.position.y /data->bit * data->square + 5, 0x00FF0000);
}