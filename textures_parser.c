/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:45:49 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/10 16:56:08 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_NO_texture(t_data *data, char **values)
{
	int i;
	
	i = 0;
	data->settings.NO = malloc(ft_strlen(values[1]) + 1);
			while (values[1][i] != '\0')
			{
				data->settings.NO[i] = values[1][i];
				i++;
			}
			data->settings.NO[i] = '\0';
			data->textures[0].img = mlx_xpm_file_to_image(data->mlx, data->settings.NO, &data->textures[0].width, &data->textures[0].height);
			data->textures[0].addr = mlx_get_data_addr(data->textures[0].img, &data->textures[0].bits_per_pixel, &data->textures[0].line_length, &data->textures[0].endian);
}

void	set_SO_texture(t_data *data, char **values)
{
	int i;
	
	i = 0;
	data->settings.SO = malloc(ft_strlen(values[1]) + 1);
			while (values[1][i] != '\0')
			{
				data->settings.SO[i] = values[1][i];
				i++;
			}
			data->settings.SO[i] = '\0';
			data->textures[1].img = mlx_xpm_file_to_image(data->mlx, data->settings.SO, &data->textures[1].width, &data->textures[1].height);
			data->textures[1].addr = mlx_get_data_addr(data->textures[1].img, &data->textures[1].bits_per_pixel, &data->textures[1].line_length, &data->textures[1].endian);
}

void	set_WE_texture(t_data *data, char **values)
{
	int i;
	
	i = 0;
	data->settings.WE = malloc(ft_strlen(values[1]) + 1);
			while (values[1][i] != '\0')
			{
				data->settings.WE[i] = values[1][i];
				i++;
			}
			data->settings.WE[i] = '\0';
			data->textures[2].img = mlx_xpm_file_to_image(data->mlx, data->settings.WE, &data->textures[2].width, &data->textures[2].height);
			data->textures[2].addr = mlx_get_data_addr(data->textures[2].img, &data->textures[2].bits_per_pixel, &data->textures[2].line_length, &data->textures[0].endian);
}

void	set_EA_texture(t_data *data, char **values)
{
	int i;
	
	i = 0;
	data->settings.EA = malloc(ft_strlen(values[1]) + 1);
			while (values[1][i] != '\0')
			{
				data->settings.EA[i] = values[1][i];
				i++;
			}
			data->settings.EA[i] = '\0';
			data->textures[3].img = mlx_xpm_file_to_image(data->mlx, data->settings.EA, &data->textures[3].width, &data->textures[3].height);
			data->textures[3].addr = mlx_get_data_addr(data->textures[3].img, &data->textures[3].bits_per_pixel, &data->textures[3].line_length, &data->textures[0].endian);
}
