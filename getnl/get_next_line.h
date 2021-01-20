/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 18:57:36 by hapryl            #+#    #+#             */
/*   Updated: 2021/01/20 19:25:56 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../lib_ft/libft.h"

int		ft_strchr_bool(const char *s, int c);
char	*ft_substr_gnl(char const *s, size_t len);

int		get_next_line(int fd, char **line);

#endif
