/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:36:34 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/26 15:47:44 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "gnl/get_next_line.h"
# include "minilibx_mms_20200219/mlx.h"
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

typedef	struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef	struct		s_dpoint
{
	double			x;
	double			y;
	double			dist;
	double			angle;
}					t_dpoint;

typedef	struct		s_player
{
	int				count;
	t_dpoint		position;
	double			fov;
	double			angle;
	double			speed;
}					t_player;

typedef	struct		s_map
{
	char			**map;
	int				width;
	int				height;
}					t_map;

typedef struct		s_smap
{
	char			line;
	void			*next;
}					t_smap;

typedef struct		s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef	struct		s_settings
{
	int				r1;
	int				r2;
	int				f;
	int				c;
	t_list			*map;
	int				size_x;
	int				size_y;
	unsigned char	has_all;
	unsigned char	flags;
}					t_settings;

typedef struct		s_all {
	void			*mlx;
	void			*mlx_win;
	t_img			img;
	t_img			textures[4];
	t_img			sprite;
	t_list			*list_s;
	t_player		player;
	t_map			map;
	t_dpoint		wall_point;
	double			*rays;
	int				square;
	int				bit;
	t_settings		settings;
	const size_t	rect_w;
	const size_t	rect_h;
}					t_all;

void				my_mlx_pixel_put(t_all *all, int x, int y, int color);

void				parser_r(t_all *all, char *line);
void				parser_fc(t_all *all, char *line);
void				parser_map(t_all *all, char *line);
void				parser_textures(t_all *all, char *line);

void				set_no_texture(t_all *all, char **values);
void				set_so_texture(t_all *all, char **values);
void				set_we_texture(t_all *all, char **values);
void				set_ea_texture(t_all *all, char **values);
void				set_s_texture(t_all *all, char **values);
void				set_map(t_all *all);

void				objects_init(t_all *all);
void				validate_map(t_all *all, int x_p, int y_p);

void				get_settings(t_all *all, char	*path);
double				get_horizontal_dist(t_all *all, double angle);
double				get_vertical_dist(t_all *all, double angle);
t_point				get_wallh(t_all *all, double angle, int i);
void				error(char *str);

void				key_w(t_all *all);
void				key_a(t_all *all);
void				key_s(t_all *all);
void				key_d(t_all *all);
void				key_r(t_all *all);
void				key_l(t_all *all);

void				my_mlx_pixel_put(t_all *all, int x, int y, int color);
unsigned int		my_mlx_get_color(t_img *img, int x, int y);
void				ft_mlx_draw_rectangle(t_all *all, t_point p1,
											t_point p2, int color);
void				ft_mlx_draw_sprites(t_all *all);
void				draw(t_all *all);

void				make_screenshot(t_all *all);

int					ft_draw_map(t_all *all, char **map);

#endif
