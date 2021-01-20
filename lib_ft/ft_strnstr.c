/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:03:43 by hapryl            #+#    #+#             */
/*   Updated: 2020/11/12 13:44:53 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char*)big);
	i = 0;
	while (big[i] && len > i)
	{
		j = 0;
		while (big[i + j] == little[j] && len + 1 > i + j && little[j] != '\0')
			j++;
		if (little[j] == '\0')
			return ((char*)&big[i]);
		i++;
	}
	return (NULL);
}
