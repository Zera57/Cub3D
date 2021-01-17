/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:58:55 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/17 19:53:20 by hapryl           ###   ########.fr       */
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
	char	arg[3] = {' ', ',', '\0'};
	int		color;

	values = ft_split_arg(line, arg);
	if (line[0] == 'R')
	{
		settings->R1 = ft_atoi(values[0]);
		settings->R2 = ft_atoi(values[1]);
	}
	color = 0;
	color += ft_atoi(values[0]) << 16;
	color += ft_atoi(values[1]) << 8;
	color += ft_atoi(values[2]);
	if (line[0] == 'F')
		settings->F = color;
	else if (line[0] == 'C')
		settings->C = color;
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