/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:58:55 by hapryl            #+#    #+#             */
/*   Updated: 2021/03/08 19:12:17 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "stdio.h"

void	parser_r(t_all *all, char *line)
{
	char	**values;

	values = ft_split(line, ' ');
	if (values[3] != NULL)
		error("Wrong arguments to Resolution");
	all->settings.r1 = check_parametr_toint(values[1]);
	all->settings.r2 = check_parametr_toint(values[2]);
	if (all->settings.r1 == 0 || all->settings.r2 == 0)
		error("param is invalid");
	all->bit = all->settings.r1;
	if (!(all->rays = malloc(sizeof(double) * all->settings.r1)))
		error("Malloc ne videlil rays");
	ft_free(values);
	free(line);
	all->settings.flags |= 0b10000000;
}

void	parser_fc(t_all *all, char *line)
{
	char	**values;
	int		color;
	int		i;

	i = 1;
	values = ft_split_arg(line, (char[2]){' ', ','});
	if (values[4] != NULL)
		error("Not valid F or C");
	while (values[i] != NULL)
	{
		if (check_parametr_toint(values[i]) > 255)
			error("Not valid F or C");
		i++;
	}
	color = check_parametr_toint(values[1]) << 16;
	color += check_parametr_toint(values[2]) << 8;
	color += check_parametr_toint(values[3]);
	fc_set(all, color, line[0]);
	ft_free(values);
	free(line);
}

void	parser_map(t_all *all, char *line)
{
	all->settings.size_x = (int)ft_strlen(line) > all->settings.size_x ?
							ft_strlen(line) : all->settings.size_x;
	if (all->settings.map == NULL)
		all->settings.map = ft_lstnew(line);
	else
		ft_lstadd_back(&all->settings.map, ft_lstnew(line));
	all->settings.size_y++;
}

void	parser_textures(t_all *all, char *line)
{
	char	**values;

	values = ft_split(line, ' ');
	if (ft_strlen(values[0]) == 2 && values[2] == NULL)
	{
		if (values[0][0] == 'N')
			set_no_texture(all, values);
		if (values[0][0] == 'S')
			set_so_texture(all, values);
		if (values[0][0] == 'W')
			set_we_texture(all, values);
		if (values[0][0] == 'E')
			set_ea_texture(all, values);
	}
	else if (ft_strlen(values[0]) == 1 && values[2] == NULL)
		if (values[0][0] == 'S')
			set_s_texture(all, values);
	ft_free(values);
	free(line);
}
