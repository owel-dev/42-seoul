/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:41:00 by ulee              #+#    #+#             */
/*   Updated: 2021/05/17 14:07:54 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceil(t_info *io)
{
	int	y;
	int	x;

	y = 0;
	while (y < io->height)
	{
		x = 0;
		while (x < io->width)
		{
			if (y > io->height / 2)
				io->buf[y][x] = io->floor_color;
			else
				io->buf[y][x] = io->ceiling_color;
			++x;
		}
		++y;
	}
}
