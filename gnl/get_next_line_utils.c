/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 18:57:12 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/17 14:19:19 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strchr_bool(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (1);
		s++;
	}
	if (*s == c)
		return (1);
	return (0);
}

char	*ft_substr_gnl(char const *s, size_t len)
{
	char	*result;
	size_t	i;

	if (!s)
		return (NULL);
	if (len <= 0)
		return (ft_strdup(""));
	if (!(result = malloc(sizeof(char) * len + 1)))
		return (result);
	i = 0;
	while (i < len && s[i] != '\n')
	{
		result[i] = s[i];
		i++;
	}
	result[i] = 0;
	return (result);
}
