/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:23:09 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/21 17:47:28 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_header(t_data *data, unsigned char *head, unsigned char *headf)
{
	unsigned char size;

	size = 14 + 40 + data->settings.R1 * data->settings.R2 * data->img.bits_per_pixel / 8;
	head[0] = 'B';
	head[1] = 'M';
	head[2] = size;
	head[3] = size>>8;
	head[4] = size>>16;
	head[5] = size>>24;
	head[10] = 54;
	head[14] = '\0';
	headf[0] = 40;
	headf[4] = data->settings.R1;
	headf[5] = data->settings.R1>>8;
	headf[6] = data->settings.R1>>16;
	headf[7] = data->settings.R1>>24;
	headf[8] = data->settings.R2;
	headf[9] = data->settings.R2>>8;
	headf[10] = data->settings.R2>>16;
	headf[11] = data->settings.R2>>24;
	headf[12] = 1;
	headf[13] = data->img.bits_per_pixel;
	headf[40] = '\0';


}

void	make_screenshot(t_data *data)
{
	int		fd;
	char	*filename;
	unsigned char *head;
	unsigned char *headf;

	filename = "screen-shot.bmp";
	ft_bzero(head, 15);
	ft_bzero(headf, 41);
	make_header(data, head, headf);
	if ((fd = open(filename, O_RDWR | O_CREAT) < 1))
		error("Screenshot failed");
	write(fd, head, 14);
	write(fd, headf, 40);
	
}
