/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 23:12:32 by zera              #+#    #+#             */
/*   Updated: 2021/02/27 14:36:15 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_draw_stripe(t_all *all, t_dp p1, t_dp p2, int id)
{
	unsigned int	color;
	double			yo;
	int				wallh;

	wallh = p1.y;
	p1.y = all->settings.r2 / 2 - wallh / 2;
	p2.y = 0;
	p2.x *= (double)all->textures[id].width;
	yo = (double)all->textures[id].height / wallh;
	if (p1.y < 0)
	{
		p2.y = (yo * wallh / 2) - (yo * all->settings.r2 / 2);
		p1.y = 0;
	}
	while (p1.y < all->settings.r2 && p2.y < all->textures[id].height)
	{
		color = my_mlx_get_color(&all->textures[id], (int)p2.x, (int)p2.y);
		my_mlx_pixel_put(all, p1.x, p1.y, color);
		p1.y++;
		p2.y += yo;
	}
}

void	ft_mlx_draw_wall(t_all *all, int x, int wallh, char c)
{
	int		id;
	t_dp	p2;

	if (c == 'n')
	{
		p2.x = ((int)all->wall_point.x % all->bit) / ((double)all->bit);
		id = 0;
	}
	if (c == 's')
	{
		p2.x = ((int)all->wall_point.x % all->bit) / ((double)all->bit);
		id = 1;
	}
	if (c == 'w')
	{
		p2.x = ((int)all->wall_point.y % all->bit) / ((double)all->bit);
		id = 2;
	}
	if (c == 'e')
	{
		p2.x = ((int)all->wall_point.y % all->bit) / ((double)all->bit);
		id = 3;
	}
	ft_mlx_draw_stripe(all, (t_dp){x, wallh, 0, 0}, p2, id);
}

void	ft_mlx_draw_walls(t_all *all)
{
	double	a;
	t_point	wallh;
	int		i;

	i = 0;
	while (i < all->settings.r1)
	{
		a = all->player.a - all->player.fov / 2
					+ all->player.fov * i / all->settings.r1;
		if (a <= 0)
			a += 2 * M_PI;
		if (a > 2 * M_PI)
			a -= 2 * M_PI;
		wallh = get_wallh(all, a, i);
		ft_mlx_draw_wall(all, i, wallh.x, wallh.y);
		i++;
	}
}

void	draw(t_all *all)
{
	ft_mlx_draw_rectangle(all, (t_point){0, 0}, (t_point){all->settings.r1,
									all->settings.r2 / 2}, all->settings.c);
	ft_mlx_draw_rectangle(all, (t_point){0, all->settings.r2 / 2 + 1},
			(t_point){all->settings.r1, all->settings.r2}, all->settings.f);
	ft_mlx_draw_walls(all);
	ft_mlx_draw_sprites(all);
}
