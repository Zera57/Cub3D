/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:24:05 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/27 16:38:00 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fc_set(t_all *all, unsigned int color, char c)
{
	if (c == 'F')
	{
		all->settings.flags |= 0b00000010;
		all->settings.f = color;
	}
	else if (c == 'C')
	{
		all->settings.flags |= 0b00000001;
		all->settings.c = color;
	}
}
