/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:57:24 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/25 18:49:29 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		set_map(t_data *data)
{
	t_list	*temp;
	int		i;
	int		height;
	int		width;

	i = 0;
	if (!(temp = data->settings.map))
		error("Hasn't map");
	height = ft_lstsize(temp);
	data->map.height = height;
	data->map.width = 0;
	if (!(data->map.map = malloc(sizeof(int*) * height)))
		error("Malloc ne videlil");
	while (temp)
	{
		if((width = ft_strlen((char*)temp->content)) > data->map.width)
			data->map.width = width;
		if (!(data->map.map[i] = malloc(sizeof(char) * width + 1)))
			error("malloc ne videlil");
		ft_strlcpy(data->map.map[i], (char*)temp->content, width);
		data->settings.map = temp;
		temp = temp->next;
		free(data->settings.map);
		i++;
	}
}

int				ft_draw_map(t_data *data, char **map)
{
	int x, y = 0;

	while (y < data->map.height)
	{
		printf("%s\n", map[y]);
		y++;
	}
	printf("\n");
	return (0);
}

int		test_map(t_data *data, char **map, int x, int y)
{
	if (map[y][x] != '1')
		map[y][x] = '1';
	else
		return (0);
	if (y - 1 < 0 || x - 1 < 0 || data->map.height <= y + 1 || data->map.width <= x + 1)
		return (1);
	if (test_map(data, map, x - 1, y) != 0)
		return (1);
	if (test_map(data, map, x, y - 1) != 0)
		return (1);
	if (test_map(data, map, x + 1, y) != 0)
		return (1);
	if (test_map(data, map, x, y + 1) != 0)
		return (1);
	return (0);
}

void		validate_map(t_data *data, int x_p, int y_p)
{
	char	**test;
	int		x, y = 0;

	if (!(test = malloc(sizeof(char*) * data->map.height + 1)))
		error("Malloc ne videlil");

	while (y < data->map.height)
	{
		if (!(test[y] = malloc(data->map.width * sizeof(char) + 1)))
			error("malloc ne videlil");
		x = 0;
		while (data->map.map[y][x] != '\0')
		{
			test[y][x] = data->map.map[y][x];
			x++;
		}
		test[y][x] = '\0';
		y++;
	}
	if (test_map(data, test, x_p, y_p) != 0)
		error("Not valid map");
}
