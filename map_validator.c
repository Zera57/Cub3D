/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:57:24 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/18 15:16:02 by hapryl           ###   ########.fr       */
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
	data->map.map = malloc(sizeof(int*) * height);
	while (temp)
	{
		if((width = ft_strlen((char*)temp->content)) > data->map.width)
			data->map.width = width;
		if (!(data->map.map[i] = malloc(sizeof(char) * width + 1)))
			error("malloc ne videlil");
		ft_strlcpy(data->map.map[i], (char*)temp->content, width);
		// printf("%s\n", (char*)temp->content);
		// printf("%s\n", data->map.map[i]);
		data->settings.map = temp;
		temp = temp->next;
		free(data->settings.map);
		i++;
	}
}

void		validate_map()
{

}