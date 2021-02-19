/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 17:54:09 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/19 17:58:23 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_l(t_data *data)
{
	if (data->player.angle <= 0)
			data->player.angle = 2*M_PI;
		data->player.angle -= 0.05;
}

void	key_r(t_data *data)
{
	if (data->player.angle >= 2 * M_PI)
		data->player.angle = 0;
	data->player.angle += 0.05;
}
