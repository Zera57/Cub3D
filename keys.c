/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 17:46:23 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/26 13:29:40 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_s(t_all *all)
{
	double	x;
	double	y;

	x = all->player.position.x - all->player.speed * cos(all->player.angle);
	y = all->player.position.y - all->player.speed * sin(all->player.angle);
	if (all->map.map[(int)(all->player.position.y /all->bit)][(int)x/all->bit] != '1')
		all->player.position.x = x;
	if (all->map.map[(int)y/all->bit][(int)all->player.position.x/all->bit] != '1')
		all->player.position.y = y;
}
	
void	key_w(t_all *all)
{
	double	x;
	double	y;

	x = all->player.position.x + all->player.speed * cos(all->player.angle);
	y = all->player.position.y + all->player.speed * sin(all->player.angle);
	if (all->map.map[(int)(all->player.position.y/all->bit)][(int)(x/all->bit)] != '1')
		all->player.position.x = x;
	if (all->map.map[(int)(y/all->bit)][(int)(all->player.position.x/all->bit)] != '1')
		all->player.position.y = y;
}
	
void	key_a(t_all *all)
{
	double	x;
	double	y;

	x = all->player.position.x - all->player.speed * cos(all->player.angle + M_PI / 2);
	y = all->player.position.y - all->player.speed * sin(all->player.angle + M_PI / 2);
	if (all->map.map[(int)(all->player.position.y/all->bit)][(int)(x/all->bit)] != '1')
		all->player.position.x = x;
	if (all->map.map[(int)(y/all->bit)][(int)(all->player.position.x/all->bit)] != '1')
		all->player.position.y = y;
}

void	key_d(t_all *all)
{
	double	x;
	double	y;

	x = all->player.position.x + all->player.speed * cos(all->player.angle + M_PI / 2);
	y = all->player.position.y + all->player.speed * sin(all->player.angle + M_PI / 2);
	if (all->map.map[(int)(all->player.position.y/all->bit)][(int)(x/all->bit)] != '1')
		all->player.position.x = x;
	if (all->map.map[(int)(y/all->bit)][(int)(all->player.position.x/all->bit)] != '1')
		all->player.position.y = y;
}