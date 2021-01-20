/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:21:10 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/17 17:03:36 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	*free_arr(char **s)
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

static	size_t	count_words(char const *s, char *c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 1;
	while (ft_strchr(c, s[i]) && s[i])
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (ft_strchr(c, s[i]))
		{
			count++;
			while (ft_strchr(c, s[i]) && s[i] != '\0')
				i++;
		}
		i++;
	}
	return (count);
}

static	char	*get_word(char const *s, char *c)
{
	size_t	i;
	char	*word;

	i = 0;
	while (s[i] != '\0' && !ft_strchr(c, s[i]))
		i++;
	i++;
	word = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(word, s, i);
	return (word);
}

char			**ft_split_arg(char const *s, char *c)
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
		if (ft_strchr(c, *s) || (i == 0 && ft_strchr(c, s[0])))
		{
			while (*s && ft_strchr(c, *s))
				s++;
			if (!(result[i] = get_word(s, c)))
				return (free_arr(result));
			i++;
		}
		s++;
	}
	result[i] = NULL;
	return (result);
}
