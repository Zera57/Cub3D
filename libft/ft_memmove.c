/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:19:56 by hapryl            #+#    #+#             */
/*   Updated: 2020/11/02 14:05:41 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *d;
	unsigned char *c;

	if (len == 0 || src == dst)
		return (dst);
	d = (unsigned char*)dst;
	c = (unsigned char*)src;
	if (d < c)
	{
		while (len--)
		{
			*d++ = *c++;
		}
	}
	else
	{
		d += len;
		c += len;
		while (len--)
		{
			*--d = *--c;
		}
	}
	return (dst);
}
