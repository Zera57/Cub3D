/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 12:23:28 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/27 14:46:17 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_draw_sprite_stripe(t_all *all, t_point start,
										t_dp offset, t_dp t)
{
	unsigned int	color;

	while (start.y <= all->settings.r2 &&
		all->sprite.height > t.y)
	{
		color = my_mlx_get_color(&all->sprite, t.x, t.y);
		my_mlx_pixel_put(all, start.x, start.y, color);
		start.y++;
		t.y += offset.y;
	}
}

void	draw_sprite(t_all *all, t_list *temp)
{
	t_point	p;
	int		wallh;

	wallh = all->settings.r2 / (((t_dp*)temp->content)->dist / all->bit);
	p.x = (((t_dp*)temp->content)->a - all->player.a + all->player.fov / 2)
			* all->settings.r1 / all->player.fov - wallh / 2;
	p.y = all->settings.r2 / 2 - wallh / 2;
	if (p.x + wallh > 0 && p.x - wallh < all->settings.r1)
		ft_mlx_draw_picture(all, p,
		(t_dp){(double)all->sprite.width / wallh,
		(double)all->sprite.height / wallh, 0, 0},
		(t_dp){wallh, ((t_dp*)temp->content)->dist, 0, 0});
}
