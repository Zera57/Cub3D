/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 13:30:53 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/25 19:26:40 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				set_S_texture(t_data *data, char **values)
{
	if (!(data->sprite.img = mlx_xpm_file_to_image(data->mlx, values[1], &data->sprite.width, &data->sprite.height)))
		error("Can't find sprite texture");
	data->sprite.addr = mlx_get_data_addr(data->sprite.img, &data->sprite.bits_per_pixel, &data->sprite.line_length, &data->textures[0].endian);
	data->settings.flags |= 0b00000100;
}
