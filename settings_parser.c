/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:58:55 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/30 15:09:37 by hapryl           ###   ########.fr       */
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
			data->settings.NO = values[1];
		if (values[0][0] == 'W')
			data->settings.WE = values[1];
		if (values[0][0] == 'S')
			data->settings.SO = values[1];
		if (values[0][0] == 'E')
			data->settings.EA = values[1];
	}
	else if (ft_strlen(values[0]) == 1 && values[2] == NULL)
		if (values[0][0] == 'S')
			data->settings.S = values[1];

	
	data->textures[0].img = mlx_xpm_file_to_image(data->mlx, data->settings.NO, &data->textures[0].width, &data->textures[0].height);
	data->textures[1].img = mlx_xpm_file_to_image(data->mlx, data->settings.SO, &data->textures[1].width, &data->textures[1].height);
	data->textures[2].img = mlx_xpm_file_to_image(data->mlx, data->settings.WE, &data->textures[2].width, &data->textures[2].height);
	data->textures[3].img = mlx_xpm_file_to_image(data->mlx, data->settings.EA, &data->textures[3].width, &data->textures[3].height);
	
	ft_free(values);
}