/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:17:49 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/18 15:10:50 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = src ? ft_strlen(src) : 0;
	if (dst && size)
	{
		len = (i > size) ? (size - 1) : i;
		ft_memcpy(dst, src, len);
		dst[len] = '\0';
	}
	return (i);
}
