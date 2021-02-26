/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:53:53 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/26 15:44:22 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dpoint	get_distance(t_all *all, t_dpoint r, t_dpoint o, double angle)
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

double		get_vertical_dist(t_all *all, double angle)
{
	t_dpoint	r;
	t_dpoint	o;
	double		ntan;

	ntan = -tan(angle);
	if (angle > M_PI_2 && angle < 3 * M_PI_2)
	{
		r.x = ((int)(all->player.position.x / all->bit) * all->bit) - 0.0001;
		r.y = (all->player.position.x - r.x) * ntan + all->player.position.y;
		o.x = -all->bit;
		o.y = -o.x * ntan;
	}
	else if (angle < M_PI_2 || angle > 3 * M_PI_2)
	{
		r.x = ((int)(all->player.position.x / all->bit) * all->bit) + all->bit;
		r.y = (all->player.position.x - r.x) * ntan + all->player.position.y;
		o.x = all->bit;
		o.y = -o.x * ntan;
	}
	else if (angle == M_PI_2 || angle == 3 * M_PI_2)
		return (all->map.height * all->bit);
	r = get_distance(all, r, o, angle);
	all->wall_point.y = r.y;
	return (fabs(fabs(r.x - all->player.position.x) / cos(angle)));
}

double		get_horizontal_dist(t_all *all, double angle)
{
	t_dpoint	r;
	t_dpoint	o;
	double		atan;

	atan = -1 / tan(angle);
	if (angle > M_PI && angle < M_PI * 2)
	{
		r.y = ((int)(all->player.position.y / all->bit) * all->bit) - 0.0001;
		r.x = (all->player.position.y - r.y) * atan + all->player.position.x;
		o.y = -all->bit;
		o.x = -o.y * atan;
	}
	else if (angle < M_PI && angle > 0)
	{
		r.y = ((int)(all->player.position.y / all->bit) * all->bit) + all->bit;
		r.x = (all->player.position.y - r.y) * atan + all->player.position.x;
		o.y = all->bit;
		o.x = -o.y * atan;
	}
	else if (angle == M_PI * 2 || angle == M_PI || angle == 0)
		return (all->map.height * all->bit);
	r = get_distance(all, r, o, angle);
	all->wall_point.x = r.x;
	return (fabs(fabs(r.y - all->player.position.y) / sin(angle)));
}

t_point		get_wallh(t_all *all, double angle, int i)
{
	int		wallh;
	double	disth;
	double	distv;
	char	side;

	if (angle > M_PI)
		side = 'n';
	else
		side = 's';
	disth = get_horizontal_dist(all, angle);
	distv = get_vertical_dist(all, angle);
	if ((distv < disth && distv >= 0) || disth < 0)
	{
		if (angle < M_PI / 2 || angle > M_PI * 3 / 2)
			side = 'e';
		else
			side = 'w';
		disth = distv;
	}
	all->rays[i] = disth;
	wallh = all->settings.r2 / (disth / all->bit *
						cos(all->player.angle - angle));
	wallh = abs(wallh);
	return ((t_point){wallh, side});
}
