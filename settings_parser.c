/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:58:55 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/10 17:00:25 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parser_R(t_data *data, char *line)
{
	char	**values;

	values = ft_split(line, ' ');

	data->settings.R1 = ft_atoi(values[0]);
	data->settings.R2 = ft_atoi(values[1]);
}

void	parser_RFC(t_data *data, char *line)
{
	char	**values;
	char	arg[2] = {' ', ','};
	int		color;

	values = ft_split_arg(line, arg);
	if (line[0] == 'R' && values[2] == NULL)
	{
		data->settings.R1 = ft_atoi(values[0]);
		data->settings.R2 = ft_atoi(values[1]);
	}
	else if (values[3] == NULL)
	{
		color = ft_atoi(values[0]) << 16;
		color += ft_atoi(values[1]) << 8;
		color += ft_atoi(values[2]);
		if (line[0] == 'F')
			data->settings.F = color;
		else if (line[0] == 'C')
			data->settings.C = color;
	}
	else
	{
		ft_free(values);
		error("Not valid R or F or C");
	}
	ft_free(values);
}

void	parser_map(t_data *data, char *line)
{
	data->settings.size_x = ft_strlen(line) > data->settings.size_x ? ft_strlen(line) : data->settings.size_x;
	if (!data->settings.map)
		data->settings.map = ft_lstnew(line);
	else
		ft_lstadd_back(&data->settings.map, ft_lstnew(line));
	data->settings.size_y++;
}

void	parser_textures(t_data *data, char *line)
{
	char	**values;

	values = ft_split(line, ' ');
	if (ft_strlen(values[0]) == 2 && values[2] == NULL)
	{
		if (values[0][0] == 'N')
		{
			set_NO_texture(data, values);
		}
		if (values[0][0] == 'S')
		{
			set_SO_texture(data, values);
		}
		if (values[0][0] == 'W')
		{
			set_WE_texture(data, values);
		}
		if (values[0][0] == 'E')
		{
			set_EA_texture(data, values);
		}
	}
	else if (ft_strlen(values[0]) == 1 && values[2] == NULL)
		if (values[0][0] == 'S')
			ft_strlcpy(	data->settings.S, values[1], 0);
	ft_free(values);
}