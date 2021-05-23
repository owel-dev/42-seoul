/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:40:51 by ulee              #+#    #+#             */
/*   Updated: 2021/05/17 14:02:57 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player(t_info *io)
{
	int	x;
	int	y;
	int	find;

	find = 0;
	y = 0;
	while (io->map[y] != NULL)
	{
		x = 0;
		while (io->map[y][x] != '\0')
		{
			if (ft_strchr(PLAYER, io->map[y][x]))
			{
				io->dir = io->map[y][x];
				io->player.x = 0.5f + x;
				io->player.y = 0.5f + y;
				++find;
			}
			++x;
		}
		++y;
	}
	if (find != 1)
		print_error("find_player");
}

void	find_sprite(t_info *io)
{
	int	x;
	int	y;

	x = 0;
	while (io->map[x])
	{
		y = 0;
		while (io->map[x][y])
		{
			if ((io->map[x][y]) == '2')
				io->num_sprite++;
			++y;
		}
		++x;
	}
}

char	*ft_strdup_blank(t_info *io, char *str)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = io->map_width;
	ret = ft_calloc(sizeof(char), (len + 1));
	if (ret == NULL)
		return (NULL);
	while (i < len)
	{
		if (str[i] != 0)
			ret[i] = str[i];
		else
		{
			while (i < len)
			{
				ret[i] = ' ';
				++i;
			}
		}
		++i;
	}
	return (ret);
}

void	duplicate_map(t_info *io)
{
	int		len;
	char	**ret;
	int		i;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (io->map_height + 1));
	if (ret == NULL)
		print_error("duplicate_map");
	while (io->map[i])
	{
		if ((int)ft_strlen(io->map[i]) < io->map_width)
			ret[i] = ft_strdup_blank(io, io->map[i]);
		else
			ret[i] = ft_strdup(io->map[i]);
		if (ret[i] == NULL)
			print_error("duplicate_map_strdup");
		len = ft_strlen(ret[i]);
		if (len > io->map_width)
			io->map_width = len;
		++i;
	}
	ret[i] = NULL;
	io->dup_map = ret;
}
