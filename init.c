/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:56:01 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/19 19:28:35 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_init(t_data *data, t_point p, char c)
{
	validate_map(data, p.x, p.y);
	data->player.position.x = (p.x + 0.5) * data->bit;
	data->player.position.y = (p.y + 0.5) * data->bit;
	data->player.fov = M_PI/3;
	data->player.dir.x = 0.5;
	data->player.dir.y = 0.5;
	data->player.planeX = 0;
	data->player.planeY = 0.66;
	data->player.speed = 0.2 * data->bit;
	if (c == 'N')
		data->player.angle = M_PI * 3 / 2;
	if (c == 'S')
		data->player.angle = M_PI / 2;
	if (c == 'W')
		data->player.angle = 0;
	if (c == 'E')
		data->player.angle = M_PI;
}

void	objects_init(t_data *data)
{
	t_point p;
	
	p.y = 0;
	while(p.y < data->map.height)
	{
		p.x = 0;
		while(p.x < data->map.width)
		{
			if (data->map.map[p.y][p.x] == '2')
			{
				t_dpoint	*dp = malloc(sizeof(t_dpoint));
				dp->x = (p.x + 0.5) * data->bit;
				dp->y = (p.y + 0.5) * data->bit;
				if (!data->list_s)
					data->list_s = ft_lstnew(dp);
				else
					ft_lstadd_front(&data->list_s, ft_lstnew(dp));
			}
			if (data->map.map[p.y][p.x] == 'N' || data->map.map[p.y][p.x] == 'S' || data->map.map[p.y][p.x] == 'W' || data->map.map[p.y][p.x] == 'E')
				player_init(data, p, data->map.map[p.y][p.x]);
			p.x++;
		}
		p.y++;
	}
}
