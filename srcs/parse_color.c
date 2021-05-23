/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:41:42 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:42:19 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color_count(char *map)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	if (map[0] != ' ')
		print_error("chek_color_count");
	if (ft_strlen(map) < 4)
		print_error("chek_color_count");
	while (map[i] != '\0')
	{
		if (map[i] == ',')
			++comma;
		if (comma > 2)
			print_error("chek_color_count");
		else if (map[i] != ' ' && map[i] != ',' && (ft_isdigit(map[i]) != 1))
			print_error("chek_color_count");
		++i;
	}
	if (comma != 2)
		print_error("chek_color_count");
}

void	check_color_space(char *map)
{
	int	i;
	int	num;
	int	space;

	i = 0;
	num = 0;
	space = 0;
	while (map[i] != '\0')
	{
		if (num == 0 && (ft_isdigit(map[i]) == 1))
			num = 1;
		else if (num == 1 && map[i] == ' ')
			space = 1;
		else if (num == 1 && space == 1 && (ft_isdigit(map[i]) == 1))
			print_error("check_color_space");
		else if (map[i] == ',')
		{
			num = 0;
			space = 0;
		}
		++i;
	}
}

void	check_color_value(t_info *io, char **color, int flag)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ft_atoi(color[i]) < 0)
			print_error("validation_color");
		else if (255 < ft_atoi(color[i]))
			print_error("validation_color");
		++i;
	}
	if (flag == F_COL && io->floor_color != -1)
		print_error("validation_color");
	else if (flag == C_COL && io->ceiling_color != -1)
		print_error("validation_color");
}

void	make_color(t_info *io, char **color, int flag)
{
	int	r;
	int	g;
	int	b;
	int	rgb;

	if (arr_len(color) != 3)
		print_error("make_color_count");
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	rgb = (r << 16) | (g << 8) | b;
	if (flag == C_COL)
		io->ceiling_color = rgb;
	else if (flag == F_COL)
		io->floor_color = rgb;
}
