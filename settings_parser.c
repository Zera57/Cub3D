/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:58:55 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/28 19:34:18 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parser_R(t_settings *settings, char *line)
{
	char	**values;

	values = ft_split(line, ' ');

	settings->R1 = ft_atoi(values[0]);
	settings->R2 = ft_atoi(values[1]);
}

void	parser_RFC(t_settings *settings, char *line)
{
	char	**values;
	char	arg[2] = {' ', ','};
	int		color;

	values = ft_split_arg(line, arg);
	if (line[0] == 'R' && values[2] == NULL)
	{
		settings->R1 = ft_atoi(values[0]);
		settings->R2 = ft_atoi(values[1]);
	}
	else if (values[3] == NULL)
	{
		color = ft_atoi(values[0]) << 16;
		color += ft_atoi(values[1]) << 8;
		color += ft_atoi(values[2]);
		if (line[0] == 'F')
			settings->F = color;
		else if (line[0] == 'C')
			settings->C = color;
	}
	else
	{
		ft_free(values);
		error("Not valid R or F or C");
	}
	ft_free(values);
}

void	parser_map(t_settings *settings, char *line)
{
	settings->size_x = ft_strlen(line) > settings->size_x ? ft_strlen(line) : settings->size_x;
	if (!settings->map)
		settings->map = ft_lstnew(line);
	else
		ft_lstadd_back(&settings->map, ft_lstnew(line));
	settings->size_y++;
}

void	parser_textures(t_settings *settings, char *line)
{
	char	**values;

	values = ft_split(line, ' ');
	if (ft_strlen(values[0]) == 2 && values[2] == NULL)
	{
		if (values[0][0] == 'N')
			settings->NO = values[1];
		if (values[0][0] == 'W')
			settings->WE = values[1];
		if (values[0][0] == 'S')
			settings->SO = values[1];
		if (values[0][0] == 'E')
			settings->EA = values[1];
	}
	else if (ft_strlen(values[0]) == 1 && values[2] == NULL)
		if (values[0][0] == 'S')
			settings->S = values[1];
}