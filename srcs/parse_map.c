/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:42:00 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:41:16 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_option(t_info *io)
{
	if (io->width == -1)
		print_error("check_option");
	else if (io->height == -1)
		print_error("check_option");
	else if (io->north_file == NULL)
		print_error("check_option");
	else if (io->south_file == NULL)
		print_error("check_option");
	else if (io->east_file == NULL)
		print_error("check_option");
	else if (io->west_file == NULL)
		print_error("check_option");
	else if (io->sprite_file == NULL)
		print_error("check_option");
	else if (io->floor_color == -1)
		print_error("check_option");
	else if (io->ceiling_color == -1)
		print_error("check_option");
}

void	link_map(t_info *io, char *line)
{
	t_list	*temp;

	temp = ft_lstnew(line);
	if (temp == NULL)
		print_error("link_map");
	if (io->li == NULL)
		io->li = temp;
	else
		ft_lstadd_back(&(io->li), temp);
}
