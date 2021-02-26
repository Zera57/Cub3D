/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:45:49 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/25 19:31:42 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_NO_texture(t_data *data, char **values)
{
	if (!(data->textures[0].img = mlx_xpm_file_to_image(data->mlx, values[1], &data->textures[0].width, &data->textures[0].height)))
		error("Can't find NO texture");
	data->textures[0].addr = mlx_get_data_addr(data->textures[0].img, &data->textures[0].bits_per_pixel, &data->textures[0].line_length, &data->textures[0].endian);
	data->settings.flags |= 0b01000000;
}

void	set_SO_texture(t_data *data, char **values)
{
	if (!(data->textures[1].img = mlx_xpm_file_to_image(data->mlx, values[1], &data->textures[1].width, &data->textures[1].height)))
		error("Can't find SO texture");
	data->textures[1].addr = mlx_get_data_addr(data->textures[1].img, &data->textures[1].bits_per_pixel, &data->textures[1].line_length, &data->textures[1].endian);
	data->settings.flags |= 0b00100000;
}

void	set_WE_texture(t_data *data, char **values)
{
	if (!(data->textures[2].img = mlx_xpm_file_to_image(data->mlx, values[1], &data->textures[2].width, &data->textures[2].height)))
		error("Can't find WE texture");
	data->textures[2].addr = mlx_get_data_addr(data->textures[2].img, &data->textures[2].bits_per_pixel, &data->textures[2].line_length, &data->textures[0].endian);
	data->settings.flags |= 0b00010000;
}

void	set_EA_texture(t_data *data, char **values)
{
	if (!(data->textures[3].img = mlx_xpm_file_to_image(data->mlx, values[1], &data->textures[3].width, &data->textures[3].height)))
		error("Can't find EA texture");
	data->textures[3].addr = mlx_get_data_addr(data->textures[3].img, &data->textures[3].bits_per_pixel, &data->textures[3].line_length, &data->textures[0].endian);
	data->settings.flags |= 0b00001000;
}
