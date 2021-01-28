/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:21:10 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/28 18:59:42 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free(char **s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static	size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 1;
	while (s[i] == c && s[i])
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			count++;
			while (s[i] == c && s[i] != '\0')
				i++;
		}
		i++;
	}
	return (count);
}

static	char	*get_word(char const *s, char c)
{
	size_t	i;
	char	*word;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	i++;
	word = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(word, s, i);
	return (word);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	if (!(result = (char **)malloc((count_words(s, c) + 1) * sizeof(char*))))
		return (result);
	i = 0;
	while (*s && count_words(s, c) != 0)
	{
		if (*s == c || (i == 0 && s[0] != c))
		{
			while (*s == c && *s)
				s++;
			if (!(result[i] = get_word(s, c)))
				return (ft_free(result));
			i++;
		}
		s++;
	}
	result[i] = NULL;
	return (result);
}
