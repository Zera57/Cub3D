/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:58:55 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/25 19:50:57 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parser_R(t_data *data, char *line)
{
	int		R1;
	int		R2;
	char	**values;

	if (values[4] != NULL)
		error("Wrong arguments to Resolution");
	values = ft_split(line, ' ');
	R1 = ft_atoi(values[1]);
	R2 = ft_atoi(values[2]);
	if (R1 < 1 || R2 < 1)
		error("Resolution is invalid it's must be greater than 0");
	if (R1 > 2560)
		R1 = 2560;
	if (R2 > 1440)
		R2 = 1440;
	data->settings.R1 = R1;
	data->settings.R2 = R2;
	data->bit = data->settings.R1;
	if (!(data->rays = malloc(sizeof(double) * data->settings.R1)))
		error("Malloc ne videlil");
	ft_free(values);
	free(line);
	data->settings.flags |= 0b10000000;
}

void	parser_FC(t_data *data, char *line)
{
	char	**values;
	char	arg[2] = {' ', ','};
	int		color;

	values = ft_split_arg(line, arg);
	if (values[4] == NULL)
	{
		color = ft_atoi(values[1]) << 16;
		color += ft_atoi(values[2]) << 8;
		color += ft_atoi(values[3]);
		if (line[0] == 'F')
		{
			data->settings.flags |= 0b00000010;
			data->settings.F = color;
		}
		else if (line[0] == 'C')
		{
			data->settings.flags |= 0b00000001;
			data->settings.C = color;
		}
	}
	else
	{
		int i = 0;
		while (values[i])
			printf("%s", values[i++]);
		ft_free(values);
		error("Not valid F or C");
	}
	ft_free(values);
	free(line);
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
			set_NO_texture(data, values);
		if (values[0][0] == 'S')
			set_SO_texture(data, values);
		if (values[0][0] == 'W')
			set_WE_texture(data, values);
		if (values[0][0] == 'E')
			set_EA_texture(data, values);
	}
	else if (ft_strlen(values[0]) == 1 && values[2] == NULL)
		if (values[0][0] == 'S')
			set_S_texture(data, values);
	ft_free(values);
	free(line);
}