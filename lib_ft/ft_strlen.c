/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:58:19 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/17 14:11:28 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *c)
{
	size_t		count;
	const char	*s;

	if (!c)
		return (0);
	s = c;
	count = 0;
	while (s[count] != '\0')
	{
		count++;
	}
	return (count);
}
