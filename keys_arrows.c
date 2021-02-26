/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 17:54:09 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/26 13:29:40 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_l(t_all *all)
{
	if (all->player.angle <= 0)
			all->player.angle = 2*M_PI;
		all->player.angle -= 0.05;
}

void	key_r(t_all *all)
{
	if (all->player.angle >= 2 * M_PI)
		all->player.angle = 0;
	all->player.angle += 0.05;
}
