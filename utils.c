/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:23:37 by hapryl            #+#    #+#             */
/*   Updated: 2021/03/08 20:10:02 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			my_mlx_pixel_put(t_all *all, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < all->settings.r1 &&
			y < all->settings.r2 && color < 0xFF000000)
	{
		dst = all->img.addr + (y * all->img.line_length
			+ x * (all->img.bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

unsigned int	my_mlx_get_color(t_img *img, int x, int y)
{
	unsigned int	color;

	color = 0x008a66e5;
	if (x >= 0 && y >= 0 && x <= img->width && y <= img->height)
		color = *(unsigned int*)(img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8)));
	return (color);
}

void			ft_mlx_draw_rectangle(t_all *all, t_point p1,
										t_point p2, int color)
{
	int		i;
	int		j;

	i = p1.y;
	while (i < p2.y)
	{
		j = p1.x;
		while (j <= p2.x)
		{
			my_mlx_pixel_put(all, j, i, color);
			j++;
		}
		i++;
	}
}

int				check_parametr_toint(char *str)
{
	int num;
	int i;

	if (!str || !ft_isdigit(*str))
		error("Param is invalid");
	num = 0;
	i = 0;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			error("Param is invalid");
		if (num > 16000)
			return (16000);
		num *= 10;
		num += *str - 48;
		str++;
	}
	return (num);
}
