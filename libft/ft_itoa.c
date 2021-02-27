/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:20:31 by hapryl            #+#    #+#             */
/*   Updated: 2020/11/05 17:12:30 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_num(int n)
{
	int		i;

	i = 0;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*result;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = count_num(n);
	if (n <= 0)
	{
		if (!(result = (char*)malloc(sizeof(char) * i + 2)))
			return (result);
		result[0] = n == 0 ? '0' : '-';
		i = i + 1;
		n *= -1;
	}
	else
		result = (char*)malloc(sizeof(char) * i + 1);
	if (!result)
		return (result);
	result[i] = '\0';
	while (i >= 0 && result[--i] != '-')
	{
		result[i] = n % 10 + 48;
		n /= 10;
	}
	return (result);
}
