/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 17:46:23 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/19 18:05:18 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_s(t_data *data)
{
	double	x;
	double	y;

	x = data->player.position.x - data->player.speed * cos(data->player.angle);
	y = data->player.position.y - data->player.speed * sin(data->player.angle);
	if (data->map.map[(int)(data->player.position.y /data->bit)][(int)x/data->bit] != '1')
		data->player.position.x = x;
	if (data->map.map[(int)y/data->bit][(int)data->player.position.x/data->bit] != '1')
		data->player.position.y = y;
}
	
void	key_w(t_data *data)
{
	double	x;
	double	y;

	x = data->player.position.x + data->player.speed * cos(data->player.angle);
	y = data->player.position.y + data->player.speed * sin(data->player.angle);
	if (data->map.map[(int)(data->player.position.y/data->bit)][(int)(x/data->bit)] != '1')
		data->player.position.x = x;
	if (data->map.map[(int)(y/data->bit)][(int)(data->player.position.x/data->bit)] != '1')
		data->player.position.y = y;
}
	
void	key_a(t_data *data)
{
	double	x;
	double	y;

	x = data->player.position.x - data->player.speed * cos(data->player.angle + M_PI / 2);
	y = data->player.position.y - data->player.speed * sin(data->player.angle + M_PI / 2);
	if (data->map.map[(int)(data->player.position.y/data->bit)][(int)(x/data->bit)] != '1')
		data->player.position.x = x;
	if (data->map.map[(int)(y/data->bit)][(int)(data->player.position.x/data->bit)] != '1')
		data->player.position.y = y;
}

void	key_d(t_data *data)
{
	double	x;
	double	y;

	x = data->player.position.x + data->player.speed * cos(data->player.angle + M_PI / 2);
	y = data->player.position.y + data->player.speed * sin(data->player.angle + M_PI / 2);
	if (data->map.map[(int)(data->player.position.y/data->bit)][(int)(x/data->bit)] != '1')
		data->player.position.x = x;
	if (data->map.map[(int)(y/data->bit)][(int)(data->player.position.x/data->bit)] != '1')
		data->player.position.y = y;
}