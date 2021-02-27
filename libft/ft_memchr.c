/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:50:52 by hapryl            #+#    #+#             */
/*   Updated: 2020/11/02 20:18:39 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *src;

	src = (unsigned char*)s;
	while (n != 0)
	{
		if (*src == (unsigned char)c)
		{
			return (src);
		}
		src++;
		n--;
	}
	return (NULL);
}
