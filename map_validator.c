/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:57:24 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/26 13:29:40 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		set_map(t_all *all)
{
	t_list	*temp;
	int		i;
	int		height;
	int		width;

	i = 0;
	if (!(temp = all->settings.map))
		error("Hasn't map");
	height = ft_lstsize(temp);
	all->map.height = height;
	all->map.width = 0;
	if (!(all->map.map = malloc(sizeof(int*) * height)))
		error("Malloc ne videlil");
	while (temp)
	{
		if((width = ft_strlen((char*)temp->content)) > all->map.width)
			all->map.width = width;
		if (!(all->map.map[i] = malloc(sizeof(char) * width + 1)))
			error("malloc ne videlil");
		ft_strlcpy(all->map.map[i], (char*)temp->content, width);
		all->settings.map = temp;
		temp = temp->next;
		ft_lstdelone(all->settings.map, free);
		i++;
	}
}

int				ft_draw_map(t_all *all, char **map)
{
	int x, y = 0;

	while (y < all->map.height)
	{
		printf("%s\n", map[y]);
		y++;
	}
	printf("\n");
	return (0);
}

int		test_map(t_all *all, char **map, int x, int y)
{
	if (map[y][x] != '1')
		map[y][x] = '1';
	else
		return (0);
	if (y - 1 < 0 || x - 1 < 0 || all->map.height <= y + 1 || all->map.width <= x + 1)
		return (1);
	if (test_map(all, map, x - 1, y) != 0)
		return (1);
	if (test_map(all, map, x, y - 1) != 0)
		return (1);
	if (test_map(all, map, x + 1, y) != 0)
		return (1);
	if (test_map(all, map, x, y + 1) != 0)
		return (1);
	return (0);
}

void		validate_map(t_all *all, int x_p, int y_p)
{
	char	**test;
	int		x, y = 0;

	if (!(test = malloc(sizeof(char*) * all->map.height + 1)))
		error("Malloc ne videlil");

	while (y < all->map.height)
	{
		if (!(test[y] = malloc(all->map.width * sizeof(char) + 1)))
			error("malloc ne videlil");
		x = 0;
		while (all->map.map[y][x] != '\0')
		{
			test[y][x] = all->map.map[y][x];
			x++;
		}
		test[y][x] = '\0';
		y++;
	}
	test[y] = NULL;
	if (test_map(all, test, x_p, y_p) != 0)
		error("Not valid map");
	ft_free(test);
}
