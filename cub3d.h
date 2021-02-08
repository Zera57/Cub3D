/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:36:34 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/08 17:48:44 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "gnl/get_next_line.h"
# include "minilibx_mms_20200219/mlx.h"
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
}					t_dpoint;

typedef	struct		s_ray
{
	double			x1;
	double			y2;
	double			x3;
	double			y4;
}					t_ray;

typedef	struct		s_player
{
	t_dpoint		position;
	t_dpoint		dir;
	double			angle;
	double			speed;
	double			planeX;
	double			planeY;
}					t_player;

typedef struct		s_smap
{
	char			line;
	void			*next;
}					t_smap;

typedef struct		s_img
{
    void			*img;
    char        	*addr;
    int         	bits_per_pixel;
    int         	line_length;
    int         	endian;
	int				width;
	int				height;
}					t_img;

typedef	struct		s_settings
{
	int				R1;
	int				R2;
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	char			*S;
	int				F;
	int				C;
	t_list			*map;
	int				size_x;
	int				size_y;
	unsigned char	has_all;
}					t_settings;

typedef struct		s_data {
    void			*mlx;
    void			*mlx_win;
	t_img			img;
	t_img			textures[4];
    t_player		player;
    int				map[10][19];
    int				square;
    t_settings		settings;
    const size_t	rect_w;
    const size_t	rect_h;
}					t_data;

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				parser_R(t_data *data, char *line);
void				parser_RFC(t_data *data, char *line);
void				parser_map(t_data *data, char *line);
void				parser_textures(t_data *data, char *line);
void				get_settings(t_data *data, char	*path);
double				get_Horizontal_dist(t_data *data, double angle);
double				get_Vertical_dist(t_data *data, double angle);
void				error(char *str);

#endif
