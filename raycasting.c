/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:53:53 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/08 16:56:28 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dpoint get_distance(t_data *data, t_dpoint r, t_dpoint o, double angle)
{
	int	dof;

	dof = 0;
	while (dof < data->settings.R1)
	{
		if (r.x/128 < 0 || r.x/128 > 19 || r.y/128 > 10 || r.y/128 < 0)
			break;
		if (data->map[(int)(r.y / 128)][(int)(r.x / 128)] == 1)
		{
			my_mlx_pixel_put(data, r.x * data->square / 128, r.y * data->square / 128, 0x0000FF00);
			return (r);
		}
		else
		{
			r.x += o.x;
			r.y += o.y;
			dof++;
		}
	}
	return (r);
}

double get_Vertical_dist(t_data *data, double angle)
{
	//Vertical
	t_dpoint	r;
	t_dpoint	o;
	double	nTan = -tan(angle);

	if (angle > M_PI_2 && angle < 3 * M_PI_2)
	{
		r.x = ((int)(data->player.position.x / 128) * 128) - 0.0001;
		r.y = (data->player.position.x - r.x) * nTan + data->player.position.y;
		o.x = -128;
		o.y = -o.x*nTan;
	}
	if (angle < M_PI_2 ||angle > 3 * M_PI_2)
	{
		r.x = ((int)(data->player.position.x / 128) * 128) + 128;
		r.y = (data->player.position.x - r.x) * nTan + data->player.position.y;
		o.x = 128;
		o.y = -o.x*nTan;
	}
	if (angle == M_PI_2 || angle == 3 * M_PI_2)
	{
		r.x = data->player.position.x;
		r.y = data->player.position.y;
		return (100000);
	}
	printf("x = %f,\ty = %f\n", r.x, r.y);
	r = get_distance(data, r, o, angle);
	return (fabs(fabs(r.y - data->player.position.y) / sin(angle)));
}

double get_Horizontal_dist(t_data *data, double angle)
{
	//Horizontal
	t_dpoint	r;
	t_dpoint	o;
	double	aTan = -1/tan(angle);

	if (angle > M_PI && angle < M_PI * 2)
	{
		r.y = ((int)(data->player.position.y / 128) * 128) - 0.0001;
		r.x = (data->player.position.y - r.y) * aTan + data->player.position.x;
		o.y = -128;
		o.x = -o.y * aTan;
	}
	if (angle < M_PI && angle > 0)
	{
		r.y = ((int)(data->player.position.y / 128) * 128) + 128;
		r.x = (data->player.position.y - r.y) * aTan + data->player.position.x;
		o.y = 128;
		o.x = -o.y * aTan;
	}
	if (angle == M_PI * 2 || angle == M_PI || angle == 0)
	{
		r.x = data->player.position.x;
		r.y = data->player.position.y;
		return 0;
	}
	r = get_distance(data, r, o, angle);
	return (fabs(fabs(r.x - data->player.position.x) / cos(angle)));
}
