/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:56:01 by hapryl            #+#    #+#             */
/*   Updated: 2021/03/07 11:53:28 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_add(t_all *all, t_point p)
{
	t_dp	*dp;

	dp = malloc(sizeof(t_dp));
	dp->x = (p.x + 0.5) * all->bit;
	dp->y = (p.y + 0.5) * all->bit;
	if (!all->list_s)
		all->list_s = ft_lstnew(dp);
	else
		ft_lstadd_front(&all->list_s, ft_lstnew(dp));
}

void	player_init(t_all *all, t_point p, char c)
{
	if (++all->player.count > 1)
		error("Two players in map");
	validate_map(all, p.x, p.y);
	all->player.position.x = (double)((double)p.x + 0.5) * (double)all->bit;
	all->player.position.y = (double)((double)p.y + 0.5) * (double)all->bit;
	all->player.fov = M_PI / 3;
	all->player.speed = 0.2 * all->bit;
	if (c == 'N')
		all->player.a = M_PI * 3 / 2;
	if (c == 'S')
		all->player.a = M_PI / 2;
	if (c == 'W')
		all->player.a = M_PI;
	if (c == 'E')
		all->player.a = 0;
}

void	objects_init(t_all *all)
{
	t_point	p;

	p.y = 0;
	all->player.count = 0;
	while (p.y < all->map.height)
	{
		p.x = 0;
		while (all->map.map[p.y][p.x] != '\0')
		{
			if (all->map.map[p.y][p.x] == '0')
				validate_map(all, p.x, p.y);
			if (all->map.map[p.y][p.x] == '2')
				sprite_add(all, p);
			if (all->map.map[p.y][p.x] == 'N' || all->map.map[p.y][p.x] == 'S'
			|| all->map.map[p.y][p.x] == 'W' || all->map.map[p.y][p.x] == 'E')
				player_init(all, p, all->map.map[p.y][p.x]);
			p.x++;
		}
		p.y++;
	}
	if (all->player.count != 1)
		error("Has no player coordinates");
}
