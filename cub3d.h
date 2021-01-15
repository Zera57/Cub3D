/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:36:34 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/15 16:30:12 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

typedef	struct		s_settings
{
	void			*content;
	struct s_list	*next;
}					t_settings;

#endif
