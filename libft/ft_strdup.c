/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:47:55 by hapryl            #+#    #+#             */
/*   Updated: 2020/11/12 13:54:07 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(s1);
	if (!(s2 = malloc(size * sizeof(char) + 1)))
		return (NULL);
	while (i < size)
	{
		s2[i] = s1[i];
		i++;
	}
	if (s2[i] != '\0')
		s2[i] = '\0';
	return (s2);
}
