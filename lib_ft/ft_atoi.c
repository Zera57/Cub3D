/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:16:24 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/17 18:51:54 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int		negative;
	long	result;
	long	tmp;

	result = 0;
	negative = 1;
	if (!str)
		return (0);
	while (*str == '\v' || *str == '\n' || *str == ' '
			|| *str == '\t' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		tmp = result;
		result = (result * 10) + *str - 48;
		if (result < tmp)
			return ((negative > 0) ? -1 : 0);
		str++;
	}
	return (result * negative);
}
