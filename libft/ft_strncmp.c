/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:58:23 by hapryl            #+#    #+#             */
/*   Updated: 2020/11/12 20:26:55 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	while (n != 0 && (*s1 || *s2))
	{
		c1 = (unsigned char)*s1++;
		c2 = (unsigned char)*s2++;
		n--;
		if (c1 != c2)
			return (c1 - c2);
	}
	return (0);
}
