/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 17:54:09 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/27 12:54:39 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_l(t_all *all)
{
	if (all->player.a <= 0)
		all->player.a = 2 * M_PI;
	all->player.a -= 0.05;
}

void	key_r(t_all *all)
{
	if (all->player.a >= 2 * M_PI)
		all->player.a = 0;
	all->player.a += 0.05;
}
