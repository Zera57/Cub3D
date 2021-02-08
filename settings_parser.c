/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:58:55 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/08 18:32:29 by hapryl           ###   ########.fr       */
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
	int i = 0;

	values = ft_split(line, ' ');
	if (ft_strlen(values[0]) == 2 && values[2] == NULL)
	{
		if (values[0][0] == 'N')
		{
			data->settings.NO = malloc(ft_strlen(values[1]) + 1);
			while (values[1][i] != '\0')
			{
				data->settings.NO[i] = values[1][i];
				i++;
			}
			data->settings.NO[i] = '\0';
		}
		if (values[0][0] == 'W')
			ft_strlcpy(data->settings.WE, values[1], 0);
		if (values[0][0] == 'S')
			ft_strlcpy(data->settings.SO, values[1], 0);
		if (values[0][0] == 'E')
			ft_strlcpy(data->settings.EA, values[1], 0);
	}
	else if (ft_strlen(values[0]) == 1 && values[2] == NULL)
		if (values[0][0] == 'S')
			ft_strlcpy(	data->settings.S, values[1], 0);

	
	data->textures[0].img = mlx_xpm_file_to_image(data->mlx, data->settings.NO, &data->textures[0].width, &data->textures[0].height);
	data->textures[0].addr = mlx_get_data_addr(data->textures[0].img, &data->textures[0].bits_per_pixel, &data->textures[0].line_length, &data->textures[0].endian);
	// data->textures[1].img = mlx_xpm_file_to_image(data->mlx, data->settings.SO, &data->textures[1].width, &data->textures[1].height);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->textures[1].img, 128, 0);
	// // data->textures[1].addr = mlx_get_data_addr(data->textures[1].img, &data->textures[1].bits_per_pixel, &data->textures[1].line_length, &data->textures[1].endian);
	// data->textures[2].img = mlx_xpm_file_to_image(data->mlx, data->settings.WE, &data->textures[2].width, &data->textures[2].height);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->textures[1].img, 256, 0);
	// // data->textures[2].addr = mlx_get_data_addr(data->textures[2].img, &data->textures[2].bits_per_pixel, &data->textures[2].line_length, &data->textures[2].endian);
	// data->textures[3].img = mlx_xpm_file_to_image(data->mlx, data->settings.EA, &data->textures[3].width, &data->textures[3].height);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->textures[1].img, 384, 0);
	// // data->textures[3].addr = mlx_get_data_addr(data->textures[3].img, &data->textures[3].bits_per_pixel, &data->textures[3].line_length, &data->textures[3].endian);
	
	ft_free(values);
}