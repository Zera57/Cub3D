/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:36:34 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/17 20:31:07 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "gnl/get_next_line.h"
# include <math.h>

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
	t_point			position;
	t_ray			direction;
	double			angle;
	int				speed;
}					t_player;

typedef struct		s_smap
{
	char			line;
	void			*next;
}					t_smap;


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

void				parser_R(t_settings *settings, char *line);
void				parser_RFC(t_settings *settings, char *line);
void				parser_map(t_settings *settings, char *line);
t_settings			*get_settings(char	*path);



#endif
