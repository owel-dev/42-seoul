/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:41:51 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 12:17:13 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		type_line(char *line)
{
	if (line[0] == 0)
		return (EMPTY_LINE);
	else if (ft_strncmp(line, "R ", 2) == 0)
		return (RESOLUTION);
	else if (is_tex(line) > 0)
		return (is_tex(line));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (F_COL);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (C_COL);
	else if (is_map(line))
		return (MAP_LINE);
	else
		print_error("CHECK_LINE_FLAG");
	return (0);
}

void	parse_resolution(t_info *io, char *line)
{
	int		i;
	char	**size;

	if (io->width != -1 || io->height != -1)
		print_error("parse_resolution_value");
	i = 1;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && (ft_isdigit(line[i]) == 0))
			print_error("parse_resolution_num");
		++i;
	}
	size = ft_split(line, ' ');
	i = 0;
	while (size[i])
		++i;
	if (i != 3)
		print_error("parse_resolution_count");
	set_screen(io, size);
	if (io->width < 1 || io->height < 1)
		print_error("parse_resolution_neg");
	arr_free(size);
}

void	parse_texture(t_info *io, char *line, int flag)
{
	char	**location;

	check_dup_texture(io, flag);
	check_xpm(line);
	location = ft_split(line, ' ');
	if (location == NULL)
		print_error("parse_texture_split");
	check_space_path(location);
	if (flag == N_TEX)
		io->north_file = ft_strdup(location[1]);
	else if (flag == W_TEX)
		io->west_file = ft_strdup(location[1]);
	else if (flag == E_TEX)
		io->east_file = ft_strdup(location[1]);
	else if (flag == S_TEX)
		io->south_file = ft_strdup(location[1]);
	else if (flag == SP_TEX)
		io->sprite_file = ft_strdup(location[1]);
	arr_free(location);
}

void	parse_color(t_info *io, char *line, int flag)
{
	char	**color;

	check_color_count(line + 1);
	check_color_space(line + 1);
	color = ft_split(line + 1, ',');
	if (color == NULL)
		print_error("parse_color");
	check_color_value(io, color, flag);
	make_color(io, color, flag);
	arr_free(color);
}

void	parse_map(t_info *io, char *line)
{
	check_option(io);
	io->is_map = 1;
	link_map(io, line);
}
