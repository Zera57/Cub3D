/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 22:53:39 by zera              #+#    #+#             */
/*   Updated: 2021/02/26 15:44:22 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void            ft_mlx_draw_picture(t_all *all, t_point start, t_dpoint offset, double wallH, double dist)
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
		y_texture = (offset.y * wallH / 2) - (offset.y * all->settings.r2 / 2);
	}
	y_temp = start.y;
	y_texture_temp = y_texture;
	while (all->sprite.width > x_texture)
	{
		if (all->rays[start.x] > dist)
		{
			start.y = y_temp;
			y_texture = y_texture_temp;
			while (start.y <= all->settings.r2 && all->sprite.height > y_texture)
			{
				color = my_mlx_get_color(&all->sprite, (int)x_texture, (int)y_texture);
					my_mlx_pixel_put(all, start.x, start.y, color);
				start.y++;
				y_texture += offset.y; 
			}
		}
		start.x++;
		x_texture += offset.x; 
	}
}

void			ft_get_distance_sprites(t_all *all)
{
	t_list	*temp;

	temp = all->list_s;
	while (temp)
	{
		((t_dpoint*)temp->content)->angle = atan2(((t_dpoint*)temp->content)->y - all->player.position.y, ((t_dpoint*)temp->content)->x - all->player.position.x);
		while (((t_dpoint*)temp->content)->angle - all->player.angle >  M_PI) ((t_dpoint*)temp->content)->angle -= 2*M_PI; 
		while (((t_dpoint*)temp->content)->angle - all->player.angle < -M_PI) ((t_dpoint*)temp->content)->angle += 2*M_PI;
		((t_dpoint*)temp->content)->dist = fabs(fabs(((t_dpoint*)temp->content)->y - all->player.position.y) / sin(((t_dpoint*)temp->content)->angle));;
		temp = temp->next;
	}
}

void			ft_sort_sprites(t_all *all)
{
	void	*c;
	t_list	*temp;

	ft_get_distance_sprites(all);
	temp = all->list_s;
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

void            ft_mlx_draw_sprites(t_all *all)
{
	t_point		p;
	t_list		*temp;

	ft_sort_sprites(all);
	temp = all->list_s;
	while (temp != NULL)
	{
		double min = all->player.angle - M_PI/2;
		double max = all->player.angle + M_PI/2;
		while (min <  0) min += 2*M_PI; 
		while (max > 2*M_PI) max -= 2*M_PI;
		if ((((t_dpoint*)temp->content)->angle > min && ((t_dpoint*)temp->content)->angle < max) || (((t_dpoint*)temp->content)->angle > min && ((t_dpoint*)temp->content)->angle > max) || (((t_dpoint*)temp->content)->angle < min && ((t_dpoint*)temp->content)->angle < max))
		{
			int		wallH = all->settings.r2 / (((t_dpoint*)temp->content)->dist / all->bit);
			p.x = (((t_dpoint*)temp->content)->angle - all->player.angle + all->player.fov / 2) * all->settings.r1 / all->player.fov - wallH / 2;
			p.y = all->settings.r2 / 2 - wallH / 2;

			if (p.x + wallH > 0 && p.x - wallH < all->settings.r1)
				ft_mlx_draw_picture(all, p, (t_dpoint){(double)all->sprite.width / wallH, (double)all->sprite.height / wallH}, wallH, ((t_dpoint*)temp->content)->dist);
		}
		temp = temp->next;
	}
}
