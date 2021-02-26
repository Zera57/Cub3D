/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:06:39 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/26 15:46:56 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			set_parametr(t_all *all, char *line)
{
	if (line[0] == 'R')
		parser_r(all, line);
	else if (line[0] == 'F' || line[0] == 'C')
		parser_fc(all, line);
	else if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		parser_textures(all, line);
	else if (line[0] == '\0')
	{
		free(line);
		return;
	}
	else 
		parser_map(all, line);
}

void			get_settings(t_all *all, char	*path)
{
	int			fd;
	char		*line;

	all->settings.size_x = 0;
	all->settings.size_y = 0;
	all->settings.has_all = 0;
	if ((fd = open(path, O_RDONLY)) <= 1)
		error("Can't find configuration file");
	while (get_next_line(fd, &line))
		set_parametr(all, line);
	set_parametr(all, line);
	if (all->settings.flags != 0b11111111)
		error("You don't have enough parametrs");
	set_map(all);
}
