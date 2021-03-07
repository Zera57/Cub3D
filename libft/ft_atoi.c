/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:16:24 by hapryl            #+#    #+#             */
/*   Updated: 2021/03/07 11:36:59 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_skip(char c)
{
	if (c == '\v' || c == '\n' || c == ' '
			|| c == '\t' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int		negative;
	long	result;
	long	tmp;

	result = 0;
	negative = 1;
	if (!str)
		return (0);
	while (is_skip(*str))
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
