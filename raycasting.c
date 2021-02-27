/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:53:53 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/27 14:38:58 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dp	get_distance(t_all *all, t_dp r, t_dp o)
{
	int	dof;

	dof = 0;
	while (dof < all->map.width + all->map.height)
	{
		if (r.x / all->bit < 0 || r.x / all->bit >= all->map.width ||
				r.y / all->bit >= all->map.height || r.y / all->bit < 0)
			break ;
		if (all->map.map[(int)(r.y / all->bit)][(int)(r.x / all->bit)] == '1')
			return (r);
		else
		{
			r.x += o.x;
			r.y += o.y;
			dof++;
		}
	}
	return (r);
}

double	get_vertical_dist(t_all *all, double a)
{
	t_dp		r;
	t_dp		o;
	double		ntan;

	ntan = -tan(a);
	if (a > M_PI_2 && a < 3 * M_PI_2)
	{
		r.x = ((int)(all->player.position.x / all->bit) * all->bit) - 0.0001;
		r.y = (all->player.position.x - r.x) * ntan + all->player.position.y;
		o.x = -all->bit;
		o.y = -o.x * ntan;
	}
	else if (a < M_PI_2 || a > 3 * M_PI_2)
	{
		r.x = ((int)(all->player.position.x / all->bit) * all->bit) + all->bit;
		r.y = (all->player.position.x - r.x) * ntan + all->player.position.y;
		o.x = all->bit;
		o.y = -o.x * ntan;
	}
	else //if (a == M_PI_2 || a == 3 * M_PI_2)
		return (all->map.height * all->bit);
	r = get_distance(all, r, o);
	all->wall_point.y = r.y;
	return (fabs(fabs(r.x - all->player.position.x) / cos(a)));
}

double	get_horizontal_dist(t_all *all, double a)
{
	t_dp		r;
	t_dp		o;
	double		atan;

	atan = -1 / tan(a);
	if (a > M_PI && a < M_PI * 2)
	{
		r.y = ((int)(all->player.position.y / all->bit) * all->bit) - 0.0001;
		r.x = (all->player.position.y - r.y) * atan + all->player.position.x;
		o.y = -all->bit;
		o.x = -o.y * atan;
	}
	else if (a < M_PI && a > 0)
	{
		r.y = ((int)(all->player.position.y / all->bit) * all->bit) + all->bit;
		r.x = (all->player.position.y - r.y) * atan + all->player.position.x;
		o.y = all->bit;
		o.x = -o.y * atan;
	}
	else //if (a == M_PI * 2 || a == M_PI || a == 0)
		return (all->map.height * all->bit);
	r = get_distance(all, r, o);
	all->wall_point.x = r.x;
	return (fabs(fabs(r.y - all->player.position.y) / sin(a)));
}

t_point	get_wallh(t_all *all, double a, int i)
{
	int		wallh;
	double	disth;
	double	distv;
	char	side;

	if (a > M_PI)
		side = 'n';
	else
		side = 's';
	disth = get_horizontal_dist(all, a);
	distv = get_vertical_dist(all, a);
	if ((distv < disth && distv >= 0) || disth < 0)
	{
		if (a < M_PI / 2 || a > M_PI * 3 / 2)
			side = 'e';
		else
			side = 'w';
		disth = distv;
	}
	all->rays[i] = disth;
	wallh = all->settings.r2 / (disth / all->bit *
						cos(all->player.a - a));
	wallh = abs(wallh);
	return ((t_point){wallh, side});
}
