/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zera <zera@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:41:39 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/25 23:20:23 by zera             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

int	            key_move(t_data *data, int keycode)
{
	double	x, y;
	int     delta_x, delta_y;
	if (keycode == 13)
		key_w(data);
	else if (keycode == 0)
		key_a(data);
	else if (keycode == 1)
		key_s(data);
	else if (keycode == 2)
		key_d(data);
	else if (keycode == 123)
		key_l(data);
	else if (keycode == 124)
		key_r(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	return (0);
}

int	            key_esc(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(1);
}

int             key_hook(int keycode, t_data *img)
{
	if ((keycode != 53))
		key_move(img, keycode);
	if (keycode == 53)
		key_esc(img);
	return (0);
}

void f(void *s)
{
	printf("|%s|\n", s);
}

void tester_parsing(t_data *data)
{
	printf("R %d %d\n", data->settings.R1, data->settings.R2);
	printf("F 0 = %d\nC 2BA5F0 = %X\n\n", data->settings.F, data->settings.C);
	printf("-----------------------------------\n");
	ft_lstiter(data->settings.map, &f);
	printf("-------------------------------\n");
	error("All good");
}

int             main(int arg, char **argv)
{
	t_data      data;

	data.mlx = mlx_init();
	get_settings(&data, argv[1]);
	data.mlx_win = mlx_new_window(data.mlx, data.settings.R1, data.settings.R2, "Hello world!");
	data.img.img = mlx_new_image(data.mlx, data.settings.R1, data.settings.R2);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, &data.img.line_length,
								&data.img.endian);

	data.square = 30;
	objects_init(&data);
	key_move(&data, -1);
	if (arg == 3 && (ft_strncmp("screenshot", argv[2], 11)) == 0)
		make_screenshot(&data);
	mlx_hook(data.mlx_win, 2, 1L<<0, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
