/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:23:37 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/19 19:25:27 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < data->settings.R1 && y < data->settings.R2 && color < 0xFF000000)
	{
		dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

unsigned int	my_mlx_get_color(t_img *img, int x, int y)
{
	unsigned int	color;

	color = 0x008a66e5;
	if (x >= 0 && y >= 0 && x <= img->width && y <= img->height)
		color = *(unsigned int*)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)));
	return (color);
}

void			ft_mlx_draw_rectangle(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	int		i;
	int		j;

	i = y1;
	while (i < y2)
	{
		j = x1;
		while (j <= x2)
		{
			my_mlx_pixel_put(data, j, i, color);
			j++;
		}
		i++;
	}
}
