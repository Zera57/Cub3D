/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:06:39 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/17 20:30:35 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include <fcntl.h>
#include "cub3d.h"
#include <unistd.h>
#include <errno.h>

void			set_parametr(t_settings *settings, char *line)
{
	if (line[0] == 'R' || line[0] == 'F' || line[0] == 'C')
		parser_RFC(settings, line);
	else if (line[0] == '\0')
		return;
	else 
		parser_map(settings, line);
}

t_settings		*get_settings(char	*path)
{
	t_settings	*settings;
	int			fd;
	char		*line;

	settings = malloc(sizeof(t_settings));
	settings->size_x = 0;
	settings->size_y = 0;
	settings->has_all = 0;
	fd = open(path, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		set_parametr(settings, line);
	}
	return (settings);
}