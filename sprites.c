/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zera <zera@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 22:53:39 by zera              #+#    #+#             */
/*   Updated: 2021/02/25 23:05:50 by zera             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
