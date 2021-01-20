/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 18:56:44 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/17 17:26:54 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	strdel(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}

int		strswitch(char **s1, char *s2)
{
	strdel(s1);
	if (!(*s1 = s2))
		return (-1);
	return (1);
}

int		ft_get_line(char **str, char **line, int fd, int r)
{
	int			lenght;

	lenght = 0;
	while (str[fd][lenght] != '\n' && str[fd][lenght] != '\0')
		lenght++;
	if (str[fd][lenght] == '\0')
	{
		if (r == BUFFER_SIZE)
			get_next_line(fd, line);
		if (!(*line = ft_strdup(str[fd])))
			return (-1);
		strdel(&str[fd]);
		return (0);
	}
	else if (str[fd][lenght] == '\n')
	{
		if (!(*line = ft_substr_gnl(str[fd], lenght)))
			return (-1);
		strswitch(&str[fd], ft_strdup(&str[fd][lenght + 1]));
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char *str[20000];
	char		buff[BUFFER_SIZE + 1];
	int			r;

	if (BUFFER_SIZE < 1 || fd < 0 || line == NULL)
	{
			return (-1);
	}
	while ((r = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[r] = '\0';
		if (str[fd] == NULL)
			if (!(str[fd] = ft_strdup("")))
				return (-1);
		if (strswitch(&str[fd], ft_strjoin(str[fd], buff)) == -1)
			return (-1);
		if (ft_strchr_bool(str[fd], '\n') == 1)
			break ;
	}
	if (r < 0)
		return (-1);
	else if (r == 0 && str[fd] == NULL)
		return (!(*line = ft_strdup("")) ? -1 : 0);
	return (ft_get_line(str, line, fd, r));
}
