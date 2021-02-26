/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:56:01 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/25 19:00:46 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_init(t_data *data, t_point p, char c)
{
	if (++data->player.count > 1)
		error("Two players in map");
	validate_map(data, p.x, p.y);
	data->player.position.x = (double)((double)p.x + 0.5) * (double)data->bit;
	data->player.position.y = (double)((double)p.y + 0.5) * (double)data->bit;
	data->player.fov = M_PI/3;
	data->player.speed = 0.2 * data->bit;
	if (c == 'N')
		data->player.angle = M_PI * 3 / 2;
	if (c == 'S')
		data->player.angle = M_PI / 2;
	if (c == 'W')
		data->player.angle = M_PI;
	if (c == 'E')
		data->player.angle = 0;
}

void	objects_init(t_data *data)
{
	t_point p;
	
	p.y = 0;
	data->player.count = 0;
	while(p.y < data->map.height)
	{
		p.x = 0;
		while(data->map.map[p.y][p.x] != '\0')
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
	if (data->player.count != 1)
		error("Has no player coordinates");
}
