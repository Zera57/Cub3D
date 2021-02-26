/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:06:39 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/25 20:05:40 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			set_parametr(t_data *data, char *line)
{
	if (line[0] == 'R')
		parser_R(data, line);
	else if (line[0] == 'F' || line[0] == 'C')
		parser_FC(data, line);
	else if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		parser_textures(data, line);
	else if (line[0] == '\0')
	{
		free(line);
		return;
	}
	else 
		parser_map(data, line);
}

void			get_settings(t_data *data, char	*path)
{
	int			fd;
	char		*line;

	data->settings.size_x = 0;
	data->settings.size_y = 0;
	data->settings.has_all = 0;
	if ((fd = open(path, O_RDONLY)) <= 1)
		error("Can't find configuration file");
	while (get_next_line(fd, &line))
		set_parametr(data, line);
	set_parametr(data, line);
	if (data->settings.flags != 0b11111111)
		error("You don't have enough parametrs");
	set_map(data);
}
