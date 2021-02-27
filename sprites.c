/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 22:53:39 by zera              #+#    #+#             */
/*   Updated: 2021/02/27 14:45:41 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_mlx_draw_picture(t_all *all, t_point start,
										t_dp offset, t_dp par)
{
	t_dp			t;

	t.x = 0;
	t.y = 0;
	if (start.y < 0)
	{
		start.y = 0;
		t.y = (offset.y * par.x / 2) - (offset.y * all->settings.r2 / 2);
	}
	while (all->sprite.width > t.x)
	{
		if (all->rays[start.x] > par.y)
			ft_mlx_draw_sprite_stripe(all, start, offset, t);
		start.x++;
		t.x += offset.x;
	}
}

void			ft_get_distance_sprites(t_all *all)
{
	t_list	*temp;

	temp = all->list_s;
	while (temp)
	{
		((t_dp*)temp->content)->a = atan2(
			((t_dp*)temp->content)->y - all->player.position.y,
			((t_dp*)temp->content)->x - all->player.position.x);
		while (((t_dp*)temp->content)->a - all->player.a > M_PI)
			((t_dp*)temp->content)->a -= 2 * M_PI;
		while (((t_dp*)temp->content)->a - all->player.a < -M_PI)
			((t_dp*)temp->content)->a += 2 * M_PI;
		((t_dp*)temp->content)->dist = fabs(((t_dp*)temp->content)->y
		- all->player.position.y) / sin(((t_dp*)temp->content)->a);
		((t_dp*)temp->content)->dist = fabs(((t_dp*)temp->content)->dist);
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
		if (((t_dp*)temp->content)->dist < ((t_dp*)temp->next->content)->dist)
		{
			c = temp->content;
			temp->content = temp->next->content;
			temp->next->content = c;
		}
		temp = temp->next;
	}
}

void			ft_mlx_draw_sprites(t_all *all)
{
	t_dp		m;
	t_list		*temp;

	ft_sort_sprites(all);
	temp = all->list_s;
	while (temp != NULL)
	{
		m.x = all->player.a - M_PI / 2;
		m.y = all->player.a + M_PI / 2;
		while (m.x < 0)
			m.x += 2 * M_PI;
		while (m.y > 2 * M_PI)
			m.y -= 2 * M_PI;
		if ((((t_dp*)temp->content)->a > m.x && ((t_dp*)temp->content)->a < m.y)
		|| (((t_dp*)temp->content)->a > m.x && ((t_dp*)temp->content)->a > m.y)
		|| (((t_dp*)temp->content)->a < m.x && ((t_dp*)temp->content)->a < m.y))
			draw_sprite(all, temp);
		temp = temp->next;
	}
}
