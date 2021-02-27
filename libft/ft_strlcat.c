/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:53:49 by hapryl            #+#    #+#             */
/*   Updated: 2020/11/04 12:50:56 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		i;
	size_t		len;

	d = dst;
	s = src;
	i = size;
	while (*d && i--)
		d++;
	len = d - dst;
	i = size - len;
	if (i <= 0)
		return (len + ft_strlen(src));
	while (*s != '\0')
	{
		if (i > 1)
		{
			i--;
			*d++ = *s;
		}
		s++;
	}
	*d = '\0';
	return (len + (s - src));
}
