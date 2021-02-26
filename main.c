/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:41:39 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/26 15:44:22 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

int	            key_move(t_all *all, int keycode)
{
	double	x, y;
	int     delta_x, delta_y;
	if (keycode == 13)
		key_w(all);
	else if (keycode == 0)
		key_a(all);
	else if (keycode == 1)
		key_s(all);
	else if (keycode == 2)
		key_d(all);
	else if (keycode == 123)
		key_l(all);
	else if (keycode == 124)
		key_r(all);
	draw(all);
	mlx_put_image_to_window(all->mlx, all->mlx_win, all->img.img, 0, 0);
	return (0);
}

int	            key_esc(t_all *all)
{
	mlx_destroy_window(all->mlx, all->mlx_win);
	exit(1);
}

int             key_hook(int keycode, t_all *img)
{
	if ((keycode != 53))
		key_move(img, keycode);
	if (keycode == 53)
		key_esc(img);
	return (0);
}

int             main(int arg, char **argv)
{
	t_all      all;

	all.mlx = mlx_init();
	get_settings(&all, argv[1]);
	all.mlx_win = mlx_new_window(all.mlx, all.settings.r1, all.settings.r2, "Hello world!");
	all.img.img = mlx_new_image(all.mlx, all.settings.r1, all.settings.r2);
	all.img.addr = mlx_get_data_addr(all.img.img, &all.img.bits_per_pixel, &all.img.line_length, &all.img.endian);

	all.square = 30;
	objects_init(&all);
	key_move(&all, -1);
	if (arg == 3 && (ft_strncmp("screenshot", argv[2], 11)) == 0)
		make_screenshot(&all);
	mlx_hook(all.mlx_win, 2, 1L<<0, key_hook, &all);
	mlx_loop(all.mlx);
	return (0);
}
