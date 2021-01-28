/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:06:39 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/28 18:56:56 by hapryl           ###   ########.fr       */
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
	else if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		parser_textures(settings, line);
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

	if (!(settings = malloc(sizeof(t_settings))))
		error("Malloc didn't allocate memory");
	settings->size_x = 0;
	settings->size_y = 0;
	settings->has_all = 0;
	if ((fd = open(path, O_RDONLY)) <= 1)
		error("Can't open file");
	while (get_next_line(fd, &line))
		set_parametr(settings, line);
	get_next_line(fd, &line);
	set_parametr(settings, line);
	return (settings);
}

void		get_textures(t_data *data)
{
	data->textures[0].img = mlx_xpm_file_to_image(data->mlx, data->settings->NO, &data->textures[0].width, &data->textures[0].height);
	free(data->settings->NO);
	data->textures[1].img = mlx_xpm_file_to_image(data->mlx, data->settings->SO, &data->textures[1].width, &data->textures[1].height);
	free(data->settings->SO);
	data->textures[2].img = mlx_xpm_file_to_image(data->mlx, data->settings->WE, &data->textures[2].width, &data->textures[2].height);
	free(data->settings->WE);
	data->textures[3].img = mlx_xpm_file_to_image(data->mlx, data->settings->EA, &data->textures[3].width, &data->textures[3].height);
	free(data->settings->EA);
	
}
