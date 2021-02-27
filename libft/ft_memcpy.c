/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:05:46 by hapryl            #+#    #+#             */
/*   Updated: 2020/10/31 13:43:19 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *d;
	unsigned char *s;

	if (n == 0 || src == dst)
		return (dst);
	if (!dst && !src)
		return (NULL);
	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	while (n != 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dst);
}
