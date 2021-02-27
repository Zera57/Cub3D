/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:45:49 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/27 12:48:26 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_no_texture(t_all *all, char **values)
{
	if (!(all->textures[0].img = mlx_xpm_file_to_image(all->mlx,
	values[1], &all->textures[0].width, &all->textures[0].height)))
		error("Can't find NO texture");
	all->textures[0].addr = mlx_get_data_addr(all->textures[0].img,
	&all->textures[0].bits_per_pixel, &all->textures[0].line_length,
	&all->textures[0].endian);
	all->settings.flags |= 0b01000000;
}

void	set_so_texture(t_all *all, char **values)
{
	if (!(all->textures[1].img = mlx_xpm_file_to_image(all->mlx,
	values[1], &all->textures[1].width, &all->textures[1].height)))
		error("Can't find SO texture");
	all->textures[1].addr = mlx_get_data_addr(all->textures[1].img,
	&all->textures[1].bits_per_pixel, &all->textures[1].line_length,
	&all->textures[1].endian);
	all->settings.flags |= 0b00100000;
}

void	set_we_texture(t_all *all, char **values)
{
	if (!(all->textures[2].img = mlx_xpm_file_to_image(all->mlx,
	values[1], &all->textures[2].width, &all->textures[2].height)))
		error("Can't find WE texture");
	all->textures[2].addr = mlx_get_data_addr(all->textures[2].img,
	&all->textures[2].bits_per_pixel, &all->textures[2].line_length,
	&all->textures[0].endian);
	all->settings.flags |= 0b00010000;
}

void	set_ea_texture(t_all *all, char **values)
{
	if (!(all->textures[3].img = mlx_xpm_file_to_image(all->mlx,
	values[1], &all->textures[3].width, &all->textures[3].height)))
		error("Can't find EA texture");
	all->textures[3].addr = mlx_get_data_addr(all->textures[3].img,
	&all->textures[3].bits_per_pixel, &all->textures[3].line_length,
	&all->textures[0].endian);
	all->settings.flags |= 0b00001000;
}
