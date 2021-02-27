/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:00:01 by hapryl            #+#    #+#             */
/*   Updated: 2020/11/04 16:18:16 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start || len <= 0)
		return (ft_strdup(""));
	if (!(result = ft_calloc(1, len + 1)))
		return (result);
	while (start-- > 0)
	{
		if (*s == '\0')
			return (result);
		s++;
	}
	return ((char*)ft_memcpy(result, s, len));
}
