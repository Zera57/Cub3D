/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 13:30:53 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/26 15:46:30 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				set_s_texture(t_all *all, char **values)
{
	if (!(all->sprite.img = mlx_xpm_file_to_image(all->mlx, values[1],
							&all->sprite.width, &all->sprite.height)))
		error("Can't find sprite texture");
	all->sprite.addr = mlx_get_data_addr(all->sprite.img,
		&all->sprite.bits_per_pixel, &all->sprite.line_length,
		&all->textures[0].endian);
	all->settings.flags |= 0b00000100;
}
