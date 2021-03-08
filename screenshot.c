/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:23:09 by hapryl            #+#    #+#             */
/*   Updated: 2021/03/08 19:56:21 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_header(t_all *all, unsigned char *head, unsigned char *headf)
{
	unsigned char size;

	size = 14 + 40 + all->settings.r1 * all->settings.r2
							* all->img.bits_per_pixel / 8;
	head[0] = 'B';
	head[1] = 'M';
	head[2] = size;
	head[3] = size >> 8;
	head[4] = size >> 16;
	head[5] = size >> 24;
	head[10] = 54;
	head[13] = '\0';
	headf[0] = 40;
	headf[4] = all->settings.r1;
	headf[5] = all->settings.r1 >> 8;
	headf[6] = all->settings.r1 >> 16;
	headf[7] = all->settings.r1 >> 24;
	headf[8] = all->settings.r2;
	headf[9] = all->settings.r2 >> 8;
	headf[10] = all->settings.r2 >> 16;
	headf[11] = all->settings.r2 >> 24;
	headf[12] = 1;
	headf[14] = all->img.bits_per_pixel;
	headf[39] = '\0';
}

void	make_screenshot(t_all *all)
{
	int				i;
	int				fd;
	char			*filename;
	unsigned char	head[14];
	unsigned char	headf[40];

	all->img.img = mlx_new_image(all->mlx, all->settings.r1,
						all->settings.r2);
	all->img.addr = mlx_get_data_addr(all->img.img,
		&all->img.bits_per_pixel, &all->img.line_length, &all->img.endian);
	key_move(all, -1);
	i = all->settings.r2;
	filename = "screen-shot.bmp";
	ft_bzero(head, 14);
	ft_bzero(headf, 40);
	make_header(all, head, headf);
	if ((fd = open(filename, O_RDWR | O_CREAT, 0755)) < 1)
		error("Screenshot failed");
	write(fd, head, 14);
	write(fd, headf, 40);
	while (i-- >= 0)
		write(fd, all->img.addr + i * all->img.line_length,
			all->img.bits_per_pixel / 8 * all->settings.r1);
	close(fd);
	exit(1);
}
