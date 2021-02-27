/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:59:31 by hapryl            #+#    #+#             */
/*   Updated: 2020/10/31 11:36:08 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char *result;

	result = 0;
	while (*s != '\0')
	{
		if (*s == c)
			result = (char*)s;
		s++;
	}
	if (*s == c)
		result = (char*)s;
	return (result);
}
