/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:58:55 by hapryl            #+#    #+#             */
/*   Updated: 2021/02/27 15:01:33 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parser_r(t_all *all, char *line)
{
	int		r1;
	int		r2;
	char	**values;

	values = ft_split(line, ' ');
	if (values[3] != NULL)
		error("Wrong arguments to Resolution");
	r1 = ft_atoi(values[1]);
	r2 = ft_atoi(values[2]);
	if (r1 < 1 || r2 < 1)
		error("Resolution is invalid it's must be greater than 0");
	if (r1 > 2560)
		r1 = 2560;
	if (r2 > 1440)
		r2 = 1440;
	all->settings.r1 = r1;
	all->settings.r2 = r2;
	all->bit = all->settings.r1;
	if (!(all->rays = malloc(sizeof(double) * all->settings.r1)))
		error("Malloc ne videlil");
	ft_free(values);
	free(line);
	all->settings.flags |= 0b10000000;
}

void	parser_fc(t_all *all, char *line)
{
	char	**values;
	int		color;
	int		i;

	i = 0;
	values = ft_split_arg(line, (char[2]){' ', ','});
	if (values[4] != NULL)
		error("Not valid F or C");
	color = ft_atoi(values[1]) << 16;
	color += ft_atoi(values[2]) << 8;
	color += ft_atoi(values[3]);
	if (line[0] == 'F')
	{
		all->settings.flags |= 0b00000010;
		all->settings.f = color;
	}
	else if (line[0] == 'C')
	{
		all->settings.flags |= 0b00000001;
		all->settings.c = color;
	}
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
