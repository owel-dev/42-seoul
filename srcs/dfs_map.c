/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:40:55 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:40:17 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dfs_map(t_info *io, char **map, int x, int y)
{
	if (x == 0 || x == io->map_height - 1 || y == 0 | y == io->map_width - 1)
	{
		io->invalid_map = 1;
		return ;
	}
	if (map[x][y] == '0' || map[x][y] == ' ' || \
		ft_strchr(PLAYER, map[x][y]) != NULL || map[x][y] == '2')
		map[x][y] = 'V';
	if (x < io->map_height - 1 && (map[x + 1][y] == '0' || \
		map[x + 1][y] == ' ' || map[x + 1][y] == '2'))
		dfs_map(io, map, x + 1, y);
	if (x > 0 && (map[x - 1][y] == '0' || map[x - 1][y] == ' ' || \
	map[x - 1][y] == '2'))
		dfs_map(io, map, x - 1, y);
	if (y < io->map_width - 1 && (map[x][y + 1] == '0' || \
	map[x][y + 1] == ' ' || map[x][y + 1] == '2'))
		dfs_map(io, map, x, y + 1);
	if (y > 0 && (map[x][y - 1] == '0' || map[x][y - 1] == ' ' || \
	map[x][y - 1] == '2'))
		dfs_map(io, map, x, y - 1);
}
