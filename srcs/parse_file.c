/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:41:45 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:41:55 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_line(t_info *io, char *line)
{
	int		flag;

	flag = type_line(line);
	if (io->is_map > 0 && (flag >= N_TEX && flag <= RESOLUTION))
		print_error("parse_line_option");
	else if (flag == EMPTY_LINE)
	{
		if (io->is_map == 1)
			io->is_map = 2;
		ft_free(line);
		return ;
	}
	else if (flag == RESOLUTION)
		parse_resolution(io, line);
	else if (flag >= N_TEX && flag <= CE_TEX)
		parse_texture(io, line, flag);
	else if (flag == F_COL || flag == C_COL)
		parse_color(io, line, flag);
	else if (io->is_map == 2 && flag == MAP_LINE)
		print_error("parse_line_newline");
	else if (flag == MAP_LINE)
		parse_map(io, line);
	if (flag != MAP_LINE)
		ft_free(line);
}

void	make_map(t_info *io)
{
	char	**ret_array;
	int		i;
	t_list	*temp;

	i = 0;
	if (io->li == NULL)
		print_error("make_map_null");
	io->map_height = ft_lstsize(io->li);
	ret_array = (char **)ft_calloc(sizeof(char *), io->map_height + 1);
	if (ret_array == NULL)
		print_error("make_map_malloc");
	while (i < io->map_height)
	{
		ret_array[i] = ft_strdup(io->li->content);
		if (io->map_width < (int)ft_strlen(ret_array[i]))
			io->map_width = ft_strlen(ret_array[i]);
		temp = io->li;
		io->li = io->li->next;
		ft_lstdelone(temp, del_list);
		++i;
	}
	ret_array[i] = NULL;
	io->map = ret_array;
}

void	check_map(t_info *io)
{
	find_player(io);
	find_sprite(io);
	duplicate_map(io);
	dfs_map(io, io->dup_map, io->player.y, io->player.x);
	arr_free(io->dup_map);
	if (io->invalid_map == 1)
		print_error("check_map_dfs");
}
