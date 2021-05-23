/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:42:13 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:40:58 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parse_info(t_info *io)
{
	io->is_map = 0;
	io->invalid_map = 0;
	io->width = -1;
	io->height = -1;
	io->map_width = 0;
	io->map_height = 0;
	io->li = NULL;
	io->east_file = NULL;
	io->west_file = NULL;
	io->south_file = NULL;
	io->north_file = NULL;
	io->sprite_file = NULL;
	io->num_sprite = 0;
	io->floor_color = -1;
	io->ceiling_color = -1;
}

void	set_pos_sprite(t_info *io, int i, int x, int y)
{
	io->sprite[i].x = 0.5f + x;
	io->sprite[i].y = 0.5f + y;
}

void	set_sprite(t_info *io)
{
	int		x;
	int		y;
	int		i;

	y = 0;
	i = 0;
	io->sprite = \
			(t_sprite *)malloc(sizeof(t_sprite) * io->num_sprite);
	if (io->sprite == NULL)
		print_error("set_sprite");
	while (y < io->map_height)
	{
		x = 0;
		while (x < io->map_width)
		{
			if (io->map[y][x] == '2')
			{
				set_pos_sprite(io, i, x, y);
				i++;
			}
			x++;
		}
		y++;
	}
}

void	parse_file(t_info *io)
{
	int		gnl_ret;
	char	*line;

	gnl_ret = 1;
	while (gnl_ret > 0)
	{
		gnl_ret = get_next_line(io->fd, &line);
		if (gnl_ret == -1)
			print_error("parse_file_gnl");
		parse_line(io, line);
	}
	if (io->is_map == 0)
		print_error("parse_file_map");
	make_map(io);
	check_map(io);
	set_sprite(io);
}
